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

#include "DDLCWordDic.h"
#include "DDWordDialog.h"

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

protected:
    void showEvent(QShowEvent *e);

private:
    Ui::MainWindow *ui;

public slots:
    void quickSearch();

    void buttonOperation(int a);

    void showMASSupport(bool b);
};
#endif // MAINWINDOW_H
