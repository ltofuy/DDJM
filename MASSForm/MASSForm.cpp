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

    isSilentBackup = false;

    giftStatusConfig=QDir::currentPath()+"/Data/Gift-Status.ini";

    QStringList headers=QStringList{tr("Name"), tr("Code"), tr("Sended"), tr("Send"), tr("Thumb")};

    //新的API, 开始增加tab
    //defaultTab
    QTabWidget *tab=ui->tabWidget;
    QWidget *widget_in_tab_default=ui->tab_clothes;
    QTableWidget *table_in_tab_default=ui->tableWidget_clothes;
    QString styleSheet_widget=widget_in_tab_default->styleSheet();
    QString styleSheet_table=table_in_tab_default->styleSheet().replace("\n", "").replace("\\n", "") + "QTableCornerButton::section{background-color: transparent;color:white;}";
    QString styleSheet_button=ui->pushButton_find->styleSheet();
    //qDebug()<<styleSheet_table;
    QSize tableSize=table_in_tab_default->size();
    QPoint tablePos=table_in_tab_default->pos();

    //初始化设置DDLC文件夹
    QSettings qSet(giftStatusConfig, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");
    QSettings qSetConfig(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSetConfig.setIniCodec("utf-8");
    ui->lineEdit_dir->setText(qSetConfig.value("ID/DDLC_path").toString());

    //在此处先检索所有的giftList
    QDir dir_ddlc(ui->lineEdit_dir->text());
    if (dir_ddlc.exists())
    {
        //使用新的API地址
        giftJsonInMods = getGiftJsonFiles(ui->lineEdit_dir->text()+"/game/mod_assets/monika/j");
        for (int i=0;i<giftJsonInMods.count();++i)
        {
            //注意, json信息确认后, 包含礼物码就都已经确认了, 不需要再读取gift文件
            //注意读取thumbs信息
            thumbFileList = getAllFiles(ui->lineEdit_dir->text()+"/game/mod_assets/thumbs");

            //使用新的方法
            //QStringList 0: code, 1, group, 2, filename, 3 displayname, 4 精确地址
            QJsonObject jObject=loadJson(giftJsonInMods.at(i).filePath());
            QString code = jObject["giftname"].toString();
            QString group = jObject["select_info"].toObject()["group"].toString();
            QString thumb = jObject["select_info"].toObject()["thumb"].toString();
            QString desplay_content = jObject["select_info"].toObject()["display_name"].toString();

            //检索精确地址
            QString thumb_abs_path = "";
            for (int j=0;j<thumbFileList.count();++j)
            {
                if (thumbFileList.at(j).filePath().toLower().endsWith(thumb.toLower()+".png"))
                {
                    //找到了;
                    thumb_abs_path = thumbFileList.at(j).filePath();
                    break;
                }
            }

            giftAllInfoList << QStringList{code, group, thumb, desplay_content, thumb_abs_path};
            if (!allTypes.contains(group))
            {
                allTypes<<group;
            }
        }

    }
    else {
        giftJsonInMods.clear();
    }

    //这里有一个强制替换dic
    QVector<QStringList> type_force_list=QVector<QStringList>{
        QStringList{"ribbon", "发带"},
        QStringList{"left-hair-clip", "左发卡"},
        QStringList{"earrings", "耳环"},
        QStringList{"choker", "项圈"},
        QStringList{"front-bow", "front-bow"},
        QStringList{"hair", "发型"},
        QStringList{"clothes", "套装"},
        QStringList{"necklace", "项链"},
        QStringList{"left-hair-flower", "左头花"},
        QStringList{"", "其它"}
    };

    //这里有一个强制禁用dic
    QStringList type_banned_list = QStringList{"hair", "front-bow"};

    //翻译
    int language = qSetConfig.value("UI/Language").toInt();

    //依据type个数进行处理
    for (int i=0;i<allTypes.count();++i)
    {
        QString subName=allTypes.at(i);

        //判断是否强制翻译
        if (language == 1)
        {
            //强制翻译;
            for (int j=0;j<type_force_list.count();++j)
            {
                if (type_force_list.at(j).first() == subName)
                {
                    subName = type_force_list.at(j).last();
                    break;
                }
            }
        }

        //判断空为other
        if (subName == "")
        {
            subName = "other";
        }

        if (i==0)
        {
            //不新增, 只增加现有
            wList.append(table_in_tab_default);
            tab->setTabText(0, subName);
        }
        else {
            //新增
            QWidget *widget=new QWidget(tab);
            //tab->setStyleSheet(styleSheet_table);
            tab->addTab(widget, subName);
            widget->setStyleSheet(styleSheet_widget);
            QTableWidget *table=new QTableWidget(widget);
            table->setStyleSheet(styleSheet_table);
            wList.append(table);
        }

        //获取最后的table并初始化设置
        QTableWidget *w=wList.data()[i];
        w->setGeometry(tablePos.rx(),tablePos.ry(), tableSize.width(), tableSize.height());

        w->setColumnCount(5);
        w->setRowCount(maxRowCount);

        w->setHorizontalHeaderLabels(headers);

        w->setColumnWidth(0, 80);
        w->setColumnWidth(1, 120);
        w->setColumnWidth(2, 80);
        w->setColumnWidth(3, 80);
        w->setColumnWidth(4, 80);

        QVector<QLabel*> labels;

        //注意这里要新建bg
        bgs.append(new QButtonGroup);
        QButtonGroup *bgc=bgs.data()[i];

        //对每个item新建
        for (int j=0;j<w->rowCount();++j)
        {
            for (int k=0;k<w->columnCount();++k)
            {
                w->setItem(j, k, new QTableWidgetItem);
                w->item(j, k)->setFlags(w->item(j, k)->flags() & ~Qt::ItemIsEnabled);
            }

            QPushButton *b=new QPushButton;
            b->setText(tr("Send"));
            b->setToolTip(tr("Send the gift to Monika"));
            w->setCellWidget(j, 3, b);
            //为了保证检索可用, 检索值应当为j+indexRow*maxRowCount
            //以确保所有的bgc都可以用1个函数来检索
            bgc->addButton(b, j + maxRowCount * i);
            b->setStyleSheet(styleSheet_button);

            //建立labels
            QLabel *l=new QLabel;
            labels<<l;
            w->setCellWidget(j, 4, l);
            l->setGeometry(0, 0, 80, 80);
            w->setRowHeight(j, 80);
        }

        //录入
        allLabels<<labels;

        //使用重写的refreshGiftStatus
        refreshGiftStatus(i);
    }

    for (int i=0;i<allTypes.count();++i)
    {
        QString subName=allTypes.at(i);

        if (type_banned_list.contains(allTypes.at(i)))
        {
            ui->tabWidget->setTabEnabled(i, false);
        }
    }


    //这里做一个判断, 如果DDLC文件夹存在, 且依据是否存在Monika化身对M2G的


    M2G = new M2GoForm;
    M2G->hide();

    refreshMonikaLove();

    bgUI.addButton(ui->pushButton_find, 0);
    bgUI.addButton(ui->pushButton_monika_love, 1);
    bgUI.addButton(ui->pushButton_MTG, 2);
    bgUI.addButton(ui->pushButton_visit_Monika, 3);
    bgUI.addButton(ui->pushButton_backups, 4);
    bgUI.addButton(ui->pushButton_reload, 5);
    bgUI.addButton(ui->pushButton_open_folder, 6);

    //所有bg链接
    for (int i=0;i<bgs.count();++i)
    {
        QButtonGroup *bg=bgs.data()[i];
        connect(bg, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperationGiftSended(int)));
    }

    connect(&bgUI, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation(int)));

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



