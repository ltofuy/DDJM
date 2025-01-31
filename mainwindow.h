#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QDir>
#include <QButtonGroup>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QShowEvent>
#include <QTimer>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSettings>
#include <QDateTime>
//#include <QDesktopServices>

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

    QMediaPlayer *mp3Player;
    QMediaPlaylist *mp3List;

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

protected:
    void showEvent(QShowEvent *e);

private:
    Ui::MainWindow *ui;

public slots:
    void quickSearch();

    void buttonOperation(int a);

    void showMASSupport(bool b);

    //自动检测更新处理;
    void autoCheckUpdate();

    //循环loop检查
    void checkFileLoopTask();
};
#endif // MAINWINDOW_H
