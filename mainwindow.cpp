#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size());

    setWindowTitle(QString(APP_NAME)+" "+QString(APP_VERSION)+" "+QString(APP_EDITION));

    tryLinkMaxCount = 5;
    tryLinkCount = 0;

    QString path=":/Resource/ddjm-d.gif";
    movie=new QMovie(path);
    movie->setScaledSize(ui->label_gif->size());
    ui->label_gif->setMovie(movie);
    movie->start();

    latestVersion = "0.12.15";

    isCheckingDownload=false;

    /*
    mp3List = new QMediaPlaylist;
    QString path_bgm=QDir::currentPath()+"/Data/bgm/Leo Young - 静秘语.mp3";
    mp3List->addMedia(QUrl::fromLocalFile(path_bgm));
    mp3List->setPlaybackMode(QMediaPlaylist::Loop);
    mp3Player = new QMediaPlayer;
    //mp3Player->setMedia(QUrl::fromLocalFile("./Data/bgm/Leo Young - 静秘语.mp3"));
    mp3Player->setPlaylist(mp3List);
    //mp3Player->play();

    //qDebug()<<QDir::currentPath()+"/Data/bgm/Leo Young - 静秘语.mp3";
    */

    wordDialog = new DDWordDialog;
    wordDialog->hide();

    ui->widget_mas->hide();
    //ui->widget_mas->setOpacity(0);

    updateJsonWidget = new UpdateJsonForm;
    updateJsonWidget->hide();

    //构建Config文件夹, 初始化json
    QString configDir=QDir::currentPath()+"/Config";
    QDir dirC(configDir);
    if (!dirC.exists())
    {
        dirC.mkpath(configDir);
    }
    if (!QFile::exists(configDir+"/config.json"))
    {
        updateJsonWidget->writeTo(configDir+"/config.json");
    }

    //若Update文件夹不存在则构建
    createDir(QDir::currentPath()+"/Update");
    //clearDir(QDir::currentPath()+"/Update");
    //clearDir(QDir::currentPath()+"/log");


    bg.addButton(ui->pushButton_word_Sayori, 0);
    bg.addButton(ui->pushButton_word_Yuri, 1);
    bg.addButton(ui->pushButton_word_Natsuki, 2);
    bg.addButton(ui->pushButton_word_Monika, 3);

    bg.addButton(ui->pushButton_find_word, 10);


    bg.addButton(ui->pushButton_get_mas, 20);
    bg.addButton(ui->pushButton_get_mas_cn, 21);

    connect(&bg, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation(int)));


    connect(ui->checkBox_MAS, SIGNAL(clicked(bool)), this, SLOT(showMASSupport(bool)));

    //构建后立即触发
    QTimer::singleShot(5*1000, this, SLOT(autoCheckUpdate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e)
{
    e->accept();

    //QTimer::singleShot(500, mp3Player, SLOT(play()));
}

void MainWindow::changeEvent(QEvent *e)
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
