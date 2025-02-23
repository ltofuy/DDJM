#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QDir>
#include <QButtonGroup>
//#include <QMediaPlayer>
//#include <QMediaPlaylist>
#include <QShowEvent>
#include <QTimer>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSettings>
#include <QDateTime>
//#include <QDesktopServices>
#include <QTranslator>

#include "DDLCWordDic.h"
#include "DDWordDialog.h"

#include "OSOperationWin.h"

#include "ez_write_log.h"
#include "UpdateJsonForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMovie *movie;

    QString latestVersion;

    //QMediaPlayer *mp3Player;
    //QMediaPlaylist *mp3List;

    QButtonGroup bg;

    DDLCWordDic wordList;

    DDWordDialog *wordDialog;

    UpdateJsonForm *updateJsonWidget;

    void createDir(QString p);
    void clearDir(QString p);

    //循环检查指定文件地址
    QString checkFilePath;

    //启动循环
    bool isInCheckLoop;

    //循环loop
    QEventLoop checkLoop;

    //trylinkCount 最大检查次数
    int tryLinkMaxCount;
    int tryLinkCount;

    //是否在检查下载情况
    bool isCheckingDownload;

    //检查下载每5s一次, 检查文件是否
    int checkingDownloadMax=100;

    //记录当前
    int checkingDownloadCurrent=0;

    //间隔
    int checkingDownloadTimeStep=5000;

    //downloadKit指定的任务名称
    QString DownloadKit_taskName="";

protected:
    void showEvent(QShowEvent *e);

    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

public slots:
    void quickSearch();

    void buttonOperation(int a);

    void showMASSupport(bool b);

    //自动检测更新处理;
    void autoCheckUpdate();

    //设置自动更新
    void enableAutoUpdate(bool b);

    //循环loop检查
    void checkFileLoopTask();

    //检查翻译
    void checkLanguage();

    //下载
    void download(QString url, QString targetFilepath);

    //专用于DownloadKit的checking, 检查目标日志
    void checkingDownloadKitWork();
};
#endif // MAINWINDOW_H
