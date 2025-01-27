#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size());

    setWindowTitle(QString(APP_NAME)+" "+QString(APP_VERSION)+" "+QString(APP_EDITION));

    QString path=":/Resource/ddjm-d.gif";
    movie=new QMovie(path);
    movie->setScaledSize(ui->label_gif->size());
    ui->label_gif->setMovie(movie);
    movie->start();

    mp3List = new QMediaPlaylist;
    QString path_bgm=QDir::currentPath()+"/Data/bgm/Leo Young - 静秘语.mp3";
    mp3List->addMedia(QUrl::fromLocalFile(path_bgm));
    mp3List->setPlaybackMode(QMediaPlaylist::Loop);
    mp3Player = new QMediaPlayer;
    //mp3Player->setMedia(QUrl::fromLocalFile("./Data/bgm/Leo Young - 静秘语.mp3"));
    mp3Player->setPlaylist(mp3List);
    //mp3Player->play();

    //qDebug()<<QDir::currentPath()+"/Data/bgm/Leo Young - 静秘语.mp3";

    wordDialog = new DDWordDialog;
    wordDialog->hide();

    ui->widget_mas->hide();
    //ui->widget_mas->setOpacity(0);

    bg.addButton(ui->pushButton_word_Sayori, 0);
    bg.addButton(ui->pushButton_word_Yuri, 1);
    bg.addButton(ui->pushButton_word_Natsuki, 2);
    bg.addButton(ui->pushButton_word_Monika, 3);

    bg.addButton(ui->pushButton_find_word, 10);

    connect(&bg, SIGNAL(buttonClicked(int)), this, SLOT(buttonOperation(int)));


    connect(ui->checkBox_MAS, SIGNAL(clicked(bool)), this, SLOT(showMASSupport(bool)));
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
