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
    wList<<ui->tableWidget_choker;
    wList<<ui->tableWidget_gifts;

    bgs<<&bg_clothes;
    bgs<<&bg_ribbon;
    bgs<<&bg_hairclip;
    bgs<<&bg_earring;
    bgs<<&bg_choker;
    bgs<<&bg_gifts;

    QStringList headers=QStringList{tr("Name"), tr("Code"), tr("Sended"), tr("Send"), tr("Thumb")};

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
        w->setColumnWidth(4, 80);

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
            b->setText(tr("Send"));
            w->setCellWidget(j, 3, b);
            bgc->addButton(b, j);

            //建立labels
            QLabel *l=new QLabel;
            labels<<l;
            w->setCellWidget(j, 4, l);
            l->setGeometry(0, 0, 80, 80);
            w->setRowHeight(j, 80);
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
    giftCode_ribbon<<QStringList{tr("Black Ribbon"), "blackribbon"};
    giftCode_ribbon<<QStringList{tr("Blue Ribbon"), "blueribbon"};
    giftCode_ribbon<<QStringList{tr("Dark-Purple Ribbon"), "darkpurpleribbon"};
    giftCode_ribbon<<QStringList{tr("Emerald Ribbon"), "emeraldribbon"};
    giftCode_ribbon<<QStringList{tr("Gray Ribbon"), "grayribbon"};
    giftCode_ribbon<<QStringList{tr("Green Ribbon"), "greenribbon"};
    giftCode_ribbon<<QStringList{tr("Light-Purple Ribbon"), "lightpurpleribbon"};
    giftCode_ribbon<<QStringList{tr("Peach Ribbon"), "peachribbon"};
    giftCode_ribbon<<QStringList{tr("Pink Ribbon"), "pinkribbon"};
    giftCode_ribbon<<QStringList{tr("Platinum Ribbon"), "platinumribbon"};
    giftCode_ribbon<<QStringList{tr("Red Ribbon"), "redribbon"};
    giftCode_ribbon<<QStringList{tr("Sapphire Ribbon"), "sapphireribbon"};
    giftCode_ribbon<<QStringList{tr("Silver Ribbon"), "silverribbon"};
    giftCode_ribbon<<QStringList{tr("Teal Ribbon"), "tealribbon"};
    giftCode_ribbon<<QStringList{tr("Yellow Ribbon"), "yellowribbon"};
    giftCode_ribbon<<QStringList{tr("Ruby Ribbon"), "rubyribbon"};
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
    giftCode_gifts<<QStringList{tr("Chocolate"), "chocolates"};
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
        targetsAllInfoList = getAllFiles(ui->lineEdit_dir->text()+"/spritepacks");
        giftFileInMods = getGiftFiles(ui->lineEdit_dir->text()+"/spritepacks");
        giftJsonInMods = getGiftJsonFiles(ui->lineEdit_dir->text()+"/spritepacks");
    }
    else {
        targetsAllInfoList.clear();

        giftFileInMods.clear();
        giftJsonInMods.clear();
    }


    //qDebug()<<targetsAllInfoList;

    //处理json数据
    //QStringList 0: code, 1, group, 2, filename
    //QVector<QStringList> giftAllInfoList;
    QStringList allTypes;
    for (int i=0;i<giftJsonInMods.count();++i)
    {
        QString contentTemp="";
        QFile f(giftJsonInMods.at(i).filePath());
        if (f.open(QIODevice::Text|QIODevice::ReadOnly))
        {
            contentTemp=QString::fromUtf8(f.readAll());
            f.close();
        }

        //处理json
        contentTemp = contentTemp.remove(" ");
        contentTemp = contentTemp.remove('"');
        contentTemp = contentTemp.remove(',');
        QStringList contentList=contentTemp.split("\n");
        QString thumb, group, giftName;
        int found = 0;
        for (int j=0;j<contentList.count();++j)
        {
            QString l=contentList.at(j);
            if (l.startsWith("thumb:"))
            {
                thumb = l.remove("thumb:").trimmed();
                found ++;
            }
            if (l.startsWith("group:"))
            {
                group = l.remove("group:").trimmed();
                found ++;
            }
            if (l.startsWith("giftname:"))
            {
                giftName = l.remove("giftname:").trimmed();
                found ++;
            }
            if (found == 3)
            {
                //不再查找;
                break;
            }
        }

        if (found == 3)
        {
            //录入信息;
            giftAllInfoList << QStringList{giftName, group, thumb};
            //qDebug()<<giftAllInfoList.last();
            if (!allTypes.contains(group))
            {
                allTypes<<group;
            }
        }
    }
    qDebug()<<"All types: "<<allTypes;


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
            case 4:
                //choker
                giftCode_choker<<QStringList{name, name};
                giftCode_choker_single<<name;
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
    refreshGiftStatus(giftCode_choker, giftStatusPath, ui->tableWidget_choker);
    refreshGiftStatus(giftCode_gifts, giftStatusPath, ui->tableWidget_gifts);

    M2G = new M2GoForm;
    M2G->hide();

    connect(&bg_clothes, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_clothes(int)));
    connect(&bg_ribbon, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_ribbon(int)));
    connect(&bg_hairclip, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_hairclip(int)));
    connect(&bg_earring, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_earring(int)));
    connect(&bg_choker, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation_choker(int)));
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



