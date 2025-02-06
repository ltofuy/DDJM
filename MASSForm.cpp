#include "MASSForm.h"
#include "ui_MASSForm.h"

MASSForm::MASSForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MASSForm)
{
    ui->setupUi(this);

    maxRowCount=256;
    wList.clear();
    bgs.clear();
    allLabels.clear();

    wList<<ui->tableWidget_clothes;
    wList<<ui->tableWidget_ribbon;
    wList<<ui->tableWidget_hairclip;
    wList<<ui->tableWidget_earring;
    wList<<ui->tableWidget_gifts;

    bgs<<&bg_clothes;
    bgs<<&bg_ribbon;
    bgs<<&bg_hairclip;
    bgs<<&bg_earring;
    bgs<<&bg_gifts;

    QStringList headers=QStringList{"Name", "Code", "Count", "Give", "Thumb"};

    isSilentBackup = false;

    for (int i=0;i<wList.count();++i)
    {
        QTableWidget *w=wList.data()[i];
        w->setColumnCount(5);
        w->setRowCount(maxRowCount);

        w->setHorizontalHeaderLabels(headers);

        w->setColumnWidth(0, 80);
        w->setColumnWidth(1, 120);
        w->setColumnWidth(2, 80);
        w->setColumnWidth(3, 80);

        QVector<QLabel*> labels;


        QButtonGroup *bgc=bgs.data()[i];

        //对每个item新建
        for (int j=0;j<w->rowCount();++j)
        {
            for (int k=0;k<w->columnCount();++k)
            {
                w->setItem(j, k, new QTableWidgetItem);

            }

            QPushButton *b=new QPushButton;
            b->setText("Give");
            w->setCellWidget(j, 3, b);
            bgc->addButton(b, j);

            //建立labels
            QLabel *l=new QLabel;
            labels<<l;
            w->setCellWidget(j, 4, l);
            l->setGeometry(0, 0, 60, 60);
            w->setRowHeight(j, 60);
        }

        //录入
        allLabels<<labels;
    }

    //录入clothes
    giftCode_clothes<<QStringList{tr("Academy Uniform"), "shuchiinacademyuniform"};
    giftCode_clothes<<QStringList{tr("Green Dress"), "greendress"};
    giftCode_clothes<<QStringList{tr("Brown Winter Jacket"), "brownwinterjacket"};
    giftCode_clothes<<QStringList{tr("A Happy Face Shirt"), "putonahappyfaceshirt"};
    giftCode_clothes<<QStringList{tr("Blue Shirt"), "blueshirt"};
    giftCode_clothes<<QStringList{tr("Rest Here Shirt"), "resthereshirt"};
    giftCode_clothes<<QStringList{tr("Blue Sweater Vest"), "bluesweatervest"};
    giftCode_clothes<<QStringList{tr("White Tanktop"), "tanktop"};
    giftCode_clothes<<QStringList{tr("Beige Turtleneck Sweater"), "beigeturtlenecksweater"};
    giftCode_clothes<<QStringList{tr("Green Hoodie"), "greenhoodie"};
    giftCode_clothes<<QStringList{tr("Black and White Striped Pullover"), "blackandwhitestripedpullover"};
    giftCode_clothes<<QStringList{tr("Wine-Asymmetrical Pullover"), "wineasymmetricalpullover"};
    giftCode_clothes<<QStringList{tr("Shell Bikini"), "shellbikini"};
    giftCode_clothes<<QStringList{tr("Shoulderless Sweater"), "shoulderlesssweater"};
    giftCode_clothes<<QStringList{tr("White and Navyblue Dress"), "whiteandnavybluedress"};
    giftCode_clothes<<QStringList{tr("Pink Shirt"), "pinkshirt"};
    for (int i=0;i<giftCode_clothes.count();++i)
    {
        giftCode_clothes_single<<giftCode_clothes.at(i).last();
    }

    //录入ribbon
    giftCode_ribbon<<QStringList{tr("Black"), "blackribbon"};
    giftCode_ribbon<<QStringList{tr("Blue"), "blueribbon"};
    giftCode_ribbon<<QStringList{tr("Dark-Purple"), "darkpurpleribbon"};
    giftCode_ribbon<<QStringList{tr("Emerald"), "emeraldribbon"};
    giftCode_ribbon<<QStringList{tr("Gray"), "grayribbon"};
    giftCode_ribbon<<QStringList{tr("Green"), "greenribbon"};
    giftCode_ribbon<<QStringList{tr("Light-Purple"), "lightpurpleribbon"};
    giftCode_ribbon<<QStringList{tr("Peach"), "peachribbon"};
    giftCode_ribbon<<QStringList{tr("Pink"), "pinkribbon"};
    giftCode_ribbon<<QStringList{tr("Platinum"), "platinumribbon"};
    giftCode_ribbon<<QStringList{tr("Red"), "redribbon"};
    giftCode_ribbon<<QStringList{tr("Sapphire"), "sapphireribbon"};
    giftCode_ribbon<<QStringList{tr("Silver"), "silverribbon"};
    giftCode_ribbon<<QStringList{tr("Teal"), "tealribbon"};
    giftCode_ribbon<<QStringList{tr("Yellow"), "yellowribbon"};
    giftCode_ribbon<<QStringList{tr("Ruby"), "rubyribbon"};
    for (int i=0;i<giftCode_ribbon.count();++i)
    {
        giftCode_ribbon_single<<giftCode_ribbon.at(i).last();
    }

    //录入other gifts
    giftCode_gifts<<QStringList{tr("Coffee"), "coffee"};
    giftCode_gifts<<QStringList{tr("Quetzal Plushie"), "quetzalplushie"};
    giftCode_gifts<<QStringList{tr("Promise Ring"), "promisering"};
    giftCode_gifts<<QStringList{tr("Candy"), "candy"};
    giftCode_gifts<<QStringList{tr("Candycorn"), "candycorn"};
    giftCode_gifts<<QStringList{tr("Hot Chocolate"), "hotchocolate"};
    giftCode_gifts<<QStringList{tr("Candycane"), "candycane"};
    giftCode_gifts<<QStringList{tr("Roses"), "roses"};
    giftCode_gifts<<QStringList{tr("Chocolate"), "chocolate"};
    giftCode_gifts<<QStringList{tr("Thermos Mug"), "justmonikathermos"};
    giftCode_gifts<<QStringList{tr("Fudge"), "fudge"};
    giftCode_gifts<<QStringList{tr("Christmas Cookies"), "christmascookies"};
    giftCode_gifts<<QStringList{tr("Cupcake"), "cupcake"};
    for (int i=0;i<giftCode_gifts.count();++i)
    {
        giftCode_other_single<<giftCode_gifts.at(i).last();
    }




    //初始化设置DDLC文件夹
    QSettings qSet(giftStatusConfig, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");
    QSettings qSetConfig(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSetConfig.setIniCodec("utf-8");
    ui->lineEdit_dir->setText(qSetConfig.value("ID/DDLC_path").toString());

    refreshMonikaLove();

    //在此处先检索所有的giftList
    QDir dir_ddlc(ui->lineEdit_dir->text());
    if (dir_ddlc.exists())
    {
        giftFileInMods = getGiftFiles(ui->lineEdit_dir->text()+"/spritepacks");
    }
    else {
        giftFileInMods.clear();
    }
    //再gifts额外增加
    for (int i=0;i<giftFileInMods.count();++i)
    {
        QFileInfo info=giftFileInMods.at(i);
        QString name=info.baseName();
        if (!giftCode_other_single.contains(name) &&
                !giftCode_ribbon_single.contains(name) &&
                !giftCode_clothes_single.contains(name))
        {
            //增加到对应分类中, 检查这个gift应当属于哪个？
            QDir dir=info.dir();
            //dir应当是gifts因此要cdup
            dir.cdUp();
            //获取monika目录下的情况
            dir = QDir(dir.path()+"/mod_assets/monika");
            switch (appearanceType(dir)) {
            case 0:
                //clothes
                giftCode_clothes<<QStringList{name, name};
                giftCode_clothes_single<<name;
                break;
            case 1:
                //ribbon
                giftCode_ribbon<<QStringList{name, name};
                giftCode_ribbon_single<<name;
                break;
            case 2:
                //hairclip
                giftCode_hairclip<<QStringList{name, name};
                giftCode_hairclip_single<<name;
                break;
            case 3:
                //earring
                giftCode_earring<<QStringList{name, name};
                giftCode_earring_single<<name;
                break;
            default:
                //others
                giftCode_gifts<<QStringList{name, name};
                giftCode_other_single<<name;
                break;
            }

            //giftCode_gifts<<QStringList{name, name};
            //giftCode_other_single<<name;
        }
    }

    QString giftStatusPath=QDir::currentPath()+"/Data/Gift-Status.ini";
    giftStatusConfig=giftStatusPath;
    refreshGiftStatus(giftCode_clothes, giftStatusPath, ui->tableWidget_clothes);
    refreshGiftStatus(giftCode_ribbon, giftStatusPath, ui->tableWidget_ribbon);
    refreshGiftStatus(giftCode_hairclip, giftStatusPath, ui->tableWidget_hairclip);
    refreshGiftStatus(giftCode_earring, giftStatusPath, ui->tableWidget_earring);
    refreshGiftStatus(giftCode_gifts, giftStatusPath, ui->tableWidget_gifts);

    M2G = new M2GoForm;
    M2G->hide();

    connect(&bg_clothes, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_clothes(int)));
    connect(&bg_ribbon, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_ribbon(int)));
    connect(&bg_hairclip, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_ribbon(int)));
    connect(&bg_earring, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_ribbon(int)));
    connect(&bg_gifts, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_gifts(int)));

    connect(ui->pushButton_find, SIGNAL(clicked()), this, SLOT(findDir()));

    connect(ui->pushButton_monika_love, SIGNAL(clicked()), this, SLOT(refreshMonikaLove()));

    connect(ui->pushButton_MTG, SIGNAL(clicked()), M2G, SLOT(show()));

    connect(ui->pushButton_visit_Monika, SIGNAL(clicked()), this, SLOT(visitMonika()));

    connect(ui->pushButton_backups, SIGNAL(clicked()), this, SLOT(makeBackup()));
    connect(ui->pushButton_reload, SIGNAL(clicked()), this, SLOT(reload()));
}

MASSForm::~MASSForm()
{
    delete ui;
}

void MASSForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
        switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
        }
}

void MASSForm::refreshGiftStatus(QVector<QStringList> giftSettings, QString configpath, QTableWidget *w)
{
    QSettings qSet(configpath, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    int index=wList.indexOf(w);
    QString sub="";
    switch (index) {
    case 0:
        sub="cloth";
        break;
    case 1:
        sub="ribbon";
    case 2:
        sub="hairclip";
    case 3:
        sub="earring";
    default:
        sub="";
        break;
    }


    for (int i=0;i<w->rowCount();++i)
    {
        if (i<giftSettings.count())
        {
            //显示
            QString code=giftSettings.at(i).at(1);
            w->setRowHidden(i, false);
            w->item(i, 0)->setText(giftSettings.at(i).at(0));
            w->item(i, 1)->setText(code);

            //查找赠送情况
            int count = qSet.value("Count/"+code).toInt();

            w->item(i, 2)->setText(QString::number(count));

            //处理code
            code = code.remove(sub+"es");
            code = code.remove(sub+"s");
            code = code.remove(sub);

            //抓thumb
            QString thatPath="";
            QDir d;
            for (int j=0; j<giftFileInMods.count();++j)
            {
                if (giftFileInMods.at(j).baseName()==code)
                {
                    thatPath=giftFileInMods.at(j).filePath();
                    d = giftFileInMods.at(j).dir();
                    d.cdUp();
                    break;
                }
            }
            if (thatPath != "")
            {
                d = QDir(d.path()+"/mod_assets/thumbs");
                QFileInfoList pngs=d.entryInfoList(QDir::Files);
                for (int k=0;k<pngs.count();++k)
                {
                    if (pngs.at(k).baseName().toLower().contains(code))
                    {
                        //载入icon
                        QLabel *ll=allLabels.data()[index].data()[i];
                        ll->setPixmap(QPixmap(pngs.at(k).filePath()));
                        ll->setScaledContents(true);
                        break;
                    }
                }
            }


        }
        else {
            //隐藏吧
            w->setRowHidden(i, true);
        }
    }
}

void MASSForm::buttonOperation_clothes(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_clothes->item(a, 0)->text(), ui->tableWidget_clothes->item(a, 1)->text());
}

void MASSForm::buttonOperation_ribbon(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_ribbon->item(a, 0)->text(), ui->tableWidget_ribbon->item(a, 1)->text());
}

void MASSForm::buttonOperation_hairclip(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_hairclip->item(a, 0)->text(), ui->tableWidget_hairclip->item(a, 1)->text());
}

void MASSForm::buttonOperation_earring(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_earring->item(a, 0)->text(), ui->tableWidget_earring->item(a, 1)->text());
}

void MASSForm::buttonOperation_gifts(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_gifts->item(a, 0)->text(), ui->tableWidget_gifts->item(a, 1)->text());

}

void MASSForm::toSendGift(QString ddlcDirPath, QString giftName, QString code)
{
    //首先判定ddlcDirPath不能为空
    QDir d(ddlcDirPath);
    if (ddlcDirPath.isEmpty() || !d.exists() || ddlcDirPath == ".")
    {
        QMessageBox::warning(NULL, "Wrong Target Folder Path", "Target folder path for DDLC is not correct!", QMessageBox::Ok);
        return;
    }

    //构造正确的characters路径
    QDir dir(ddlcDirPath+"/characters");
    if (!dir.exists())
    {
        //qDebug()<<dir.path();
        dir.mkdir(dir.path());
    }
    if (!dir.exists())
    {
        QMessageBox::warning(NULL, "Wrong Target Folder Path", "Target folder path for DDLC is not correct!", QMessageBox::Ok);
        return;
    }

    //确认赠送
    QSettings qSet(giftStatusConfig, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    int count=qSet.value("Count/"+code).toInt();

    QString content;
    content = "Are sure to send the gift "+giftName+" to dear Monika?"+"\n";
    content += "You have already sended: "+QString::number(count)+".";
    QMessageBox::StandardButton a = QMessageBox::information(NULL, "", content, QMessageBox::Yes|QMessageBox::No);
    if (a == QMessageBox::Yes)
    {
        QFile f(dir.path()+"/"+code+".gift");
        if (f.open(QIODevice::Text|QIODevice::WriteOnly))
        {
            f.write("To my dear Monika");
            f.close();
        }

        if (f.exists())
        {
            QMessageBox::information(NULL, "", "Gift sended successful");
            qSet.setValue("Count/"+code, count+1);

            refreshGiftStatus(giftCode_clothes, giftStatusConfig, ui->tableWidget_clothes);
            refreshGiftStatus(giftCode_ribbon, giftStatusConfig, ui->tableWidget_ribbon);
            refreshGiftStatus(giftCode_gifts, giftStatusConfig, ui->tableWidget_gifts);
        }
        else {
            QMessageBox::information(NULL, "", "Gift sended failed, please check the operation privileges");
        }
    }
}

void MASSForm::findDir()
{
    QString fdpath=QFileDialog::getExistingDirectory(NULL, "Select DDLC Folder", QDir::currentPath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if (!fdpath.isEmpty())
    {
        ui->lineEdit_dir->setText(fdpath);
        QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
        qSet.setIniCodec("utf-8");

        qSet.setValue("ID/DDLC_path", fdpath);
        qSet.sync();
    }
}

void MASSForm::refreshMonikaLove()
{
    QDir d(ui->lineEdit_dir->text());
    if (d.exists() && !ui->lineEdit_dir->text().isEmpty())
    {
        //查找好感度
        QFile f(ui->lineEdit_dir->text()+"/log/aff_log.log");
        if (!f.exists())
        {
            ui->label_monika_love->setText("???");
            return;
        }
        if (f.open(QIODevice::Text|QIODevice::ReadOnly))
        {
            QString content=QString::fromUtf8(f.readAll());
            QStringList list=content.split("\n");

            //qDebug()<<list;

            for (int i=0;i<list.count();++i)
            {
                //反向检索;
                int index=list.count()-1-i;
                QString l=list.at(index);
                l=l.remove(" ");
                if (l.count() == 0)
                {
                    continue;
                }

                QStringList part_list=l.split(":SAVE|");
                if (part_list.count()==2)
                {
                    ui->label_monika_love->setText(part_list.at(1));
                    break;
                }
            }

            f.close();
        }
    }
}


QFileInfoList MASSForm::getGiftFiles(QString directoryPath) {
    QFileInfoList fileInfoList;
    QDir dir(directoryPath);
    if (!dir.exists()) {
        return fileInfoList; // 返回空列表如果目录不存在
    }
    // 查找所有后缀为.gift的文件，递归搜索子目录
    fileInfoList = dir.entryInfoList(QStringList() << "*.gift", QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    // 获取子目录
    QFileInfoList subDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &subDirInfo : subDirs) {
        QFileInfoList subFiles = getGiftFiles(subDirInfo.absoluteFilePath());
        fileInfoList.append(subFiles); // 递归得到的文件添加到列表中
    }
    return fileInfoList;
}
