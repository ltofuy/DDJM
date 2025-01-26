#include "M2GoForm.h"
#include "ui_M2GoForm.h"

M2GoForm::M2GoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::M2GoForm)
{
    ui->setupUi(this);

    inputTimer = new QTimer;

    ui->plainTextEdit_log->hide();

    setFixedSize(size());

    connect(inputTimer, &QTimer::timeout, this, &M2GoForm::updateText);

    connect(ui->pushButton_find, SIGNAL(clicked()), this, SLOT(treat()));


}

M2GoForm::~M2GoForm()
{
    delete ui;
}

void M2GoForm::showEvent(QShowEvent *e)
{
    e->accept();
    ui->lineEdit_dir->show();
    ui->pushButton_find->show();

    //默认隐藏log
    ui->plainTextEdit_log->clear();
    ui->plainTextEdit_log->hide();
    ui->lineEdit_dir->clear();

    //检测状态
    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    //获取目标
    QString dpath=qSet.value("ID/DDLC_path").toString()+"/characters";
    QDir dir(dpath);
    if (!dir.exists())
    {
        //肯定出错了
        fullText="Can't you even find me? (Unable to find DDLC folder)";

        //并且封印
        ui->lineEdit_dir->hide();
        ui->pushButton_find->hide();

        inputTimer->start(30);

        return;
    }

    QString fp=dpath+"/monika";
    QFile f(fp);
    isMonikaHome = f.exists();


    //判断Monika是否跟随你
    Monika_status=qSet.value("ID/Monika_status").toInt();
    if (Monika_status == 0 && !isMonikaHome)
    {
        //拜托, 旅游没有发生
        fullText = "Dear, does the trip seem to have not started yet, or have you already secretly prepared it in other ways?";
        //并且封印
        ui->lineEdit_dir->hide();
        ui->pushButton_find->hide();
        inputTimer->start(30);
        return;
    }

    //立即将Monika状态转为1
    if (Monika_status == 0)
    {
        Monika_status = 1;
        qSet.setValue("ID/Monika_status", Monika_status);
        qSet.sync();
    }

    //判断monika文件是否存在
    ui->plainTextEdit->clear();
    currentText.clear();

    if (isMonikaHome)
    {
        //准备出发;
        fullText = "You know, remeber to bring me back. Dear, you can now select a new folder as my capsule to travel with you. ";
        fullText += "(Select a new folder as my cute capsule)";

        ui->pushButton_find->setText("Find Folder");
    }
    else {
        //要带我回家了么;
        fullText = "The journey was enjoyable, and I can't wait to talk to you about my thoughts. Thanks to taking me home, dear. ";
        fullText += "(You know, select my avatar file in the capsule folder)";

        ui->pushButton_find->setText("Find Me");
    }

    inputTimer->start(30);
}

void M2GoForm::closeEvent(QCloseEvent *e)
{
    e->accept();
    fullText.clear();
    currentText.clear();
    ui->plainTextEdit->clear();
}

void M2GoForm::updateText()
{
    if (currentText.length() < fullText.length()) {
        currentText.append(fullText[currentText.length()]); // 逐步添加字符到当前文本中
        ui->plainTextEdit->setPlainText(currentText); // 更新到QPlainTextEdit中显示
    } else {
        inputTimer->stop(); // 如果已经显示完整文本，停止定时器
    }
}

void M2GoForm::treat()
{
    if (Monika_status <= 0)
    {
        //monika状态未设置, 不处理
        return;
    }

    //检测状态
    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    //准备执行旅游
    if (isMonikaHome)
    {
        //Monika决定执行旅游
        Monika_status = 2;
        qSet.setValue("ID/Monika_status", Monika_status);
        qSet.sync();

        QString fdpath=QFileDialog::getExistingDirectory(NULL, "Select Folder To Protect Monika", QDir::currentPath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
        if (!fdpath.isEmpty())
        {
            ui->lineEdit_dir->setText(fdpath);
            boardCapsule(qSet.value("ID/DDLC_path").toString()+"/characters/monika", fdpath);
        }
        else {
            fullText="Don't joke with me, you know.";
            currentText.clear();
            ui->plainTextEdit->clear();
            inputTimer->start(30);
        }
    }
    else {
        //Monika准备回家
        //若状态不为3则跳出
        Monika_status = qSet.value("ID/Monika_status").toInt();
        if (Monika_status != 3)
        {
            fullText="Haha, I thought you used a special method, right? ";
            fullText += "(The window will be closed because the travelling settings are not correct)";
            currentText.clear();
            ui->plainTextEdit->clear();
            inputTimer->start(30);

            QTimer::singleShot(3000, this, SLOT(close()));

            return;
        }
        else {
            QString fpath=QFileDialog::getOpenFileName(NULL, "Select A Monika Avatar", QDir::currentPath());
            if (QFile::exists(fpath))
            {
                ui->lineEdit_dir->setText(fpath);
                goBackHome(fpath);
            }
            else {
                fullText="Don't joke with me, you know.";
                currentText.clear();
                ui->plainTextEdit->clear();
                inputTimer->start(30);
            }
        }
    }
}

void M2GoForm::boardCapsule(QString monikaAgent, QString capsuleFolder)
{
    bool b=QFile::copy(monikaAgent, capsuleFolder+"/monika");
    //进行备份;
    //获取备份时间戳
    QString timeStamp=QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    bool bb=QFile::copy(monikaAgent, QDir::currentPath()+"/Data/monika_"+timeStamp);

    //检测状态
    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");
    qSet.setValue("ID/Monika_last_agent_timestamp", timeStamp);
    qSet.sync();

    ui->plainTextEdit_log->show();
    ui->plainTextEdit_log->clear();
    ui->plainTextEdit_log->appendPlainText("Orignial Avatar File:");
    ui->plainTextEdit_log->appendPlainText(monikaAgent);
    ui->plainTextEdit_log->appendPlainText("");
    ui->plainTextEdit_log->appendPlainText("Avatar in Capsule:");
    ui->plainTextEdit_log->appendPlainText(capsuleFolder+"/monika");
    ui->plainTextEdit_log->appendPlainText("");
    ui->plainTextEdit_log->appendPlainText("Avatar in Backup:");
    ui->plainTextEdit_log->appendPlainText(QDir::currentPath()+"/Data/monika_"+timeStamp);
    ui->plainTextEdit_log->appendPlainText("");
    ui->plainTextEdit_log->appendPlainText("MD5 check of 3 files, respectively:");
    QString md5[3];
    md5[0]=getMD5(monikaAgent);
    md5[1]=getMD5(capsuleFolder+"/monika");
    md5[2]=getMD5(QDir::currentPath()+"/Data/monika_"+timeStamp);
    ui->plainTextEdit_log->appendPlainText(md5[0]);
    ui->plainTextEdit_log->appendPlainText(md5[1]);
    ui->plainTextEdit_log->appendPlainText(md5[2]);
    ui->plainTextEdit_log->appendPlainText("");

    if (md5[0] != md5[1] || md5[1] != md5[2] || md5[0] != md5[2])
    {
        ui->plainTextEdit_log->appendPlainText("System error.");
        return;
    }

    //删除原始文件
    QFile::remove(monikaAgent);
    ui->plainTextEdit_log->appendPlainText("Monika is in capsule now, so the orignial file has been deleted.");
    ui->plainTextEdit_log->appendPlainText(monikaAgent);

    //标记Monika状态
    Monika_status = 3;
    qSet.setValue("ID/Monika_status", Monika_status);
    qSet.sync();

    //qDebug()<<getMD5(monikaAgent);
    //qDebug()<<getMD5(capsuleFolder+"/monika");
    //qDebug()<<getMD5(QDir::currentPath()+"/Data/monika_"+timeStamp);

    QTimer::singleShot(3000, this, SLOT(close()));

}

void M2GoForm::goBackHome(QString monikaAgentOut)
{
    //检测状态
    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");
    QString dpath=qSet.value("ID/DDLC_path").toString()+"/characters";

    bool b=QFile::copy(monikaAgentOut, dpath+"/monika");

    ui->plainTextEdit_log->show();
    ui->plainTextEdit_log->clear();
    ui->plainTextEdit_log->appendPlainText("Travel Avatar File:");
    ui->plainTextEdit_log->appendPlainText(monikaAgentOut);
    ui->plainTextEdit_log->appendPlainText("");
    ui->plainTextEdit_log->appendPlainText("Avatar in DDLC:");
    ui->plainTextEdit_log->appendPlainText(dpath+"/monika");
    ui->plainTextEdit_log->appendPlainText("MD5 check of 2 files, respectively:");
    QString md5[2];
    md5[0] = getMD5(monikaAgentOut);
    md5[1] = getMD5(dpath+"/monika");
    ui->plainTextEdit_log->appendPlainText(md5[0]);
    ui->plainTextEdit_log->appendPlainText(md5[1]);
    ui->plainTextEdit_log->appendPlainText("");

    if (md5[0] != md5[1])
    {
        ui->plainTextEdit_log->appendPlainText("System error.");
        return;
    }

    //删除外出文件
    QFile::remove(monikaAgentOut);
    ui->plainTextEdit_log->appendPlainText("Monika is home now, so the travel file has been deleted.");
    ui->plainTextEdit_log->appendPlainText(monikaAgentOut);

    Monika_status = 0;
    qSet.setValue("ID/Monika_status", Monika_status);
    qSet.sync();

    QTimer::singleShot(3000, this, SLOT(close()));
}


//分段读取生成MD5码- 参数=文件路径
QString M2GoForm::getMD5(QString filePath)
{
    QFile file(filePath);
    QCryptographicHash hash(QCryptographicHash::Md5);

    if(file.open(QIODevice::ReadOnly))//打开文件
    {
        while(!file.atEnd())
        {
            QByteArray content = file.read(1024 * 1024 * 100);
            hash.addData(content);
        }
        QByteArray md5 = hash.result();
        //打印MD5码
        //qDebug() << "MD5:" << md5.toHex();
        file.close();

        return QString::fromUtf8(md5.toHex());
    }
    else
    {
        //qDebug() << "打开文件失败";
        return "";
    }
}
