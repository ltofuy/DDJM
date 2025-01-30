#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //依据新标准定义程序运行目录
    QString appDir=qApp->applicationDirPath();
    if (appDir.lastIndexOf("/bin")!=-1)
    {
        QDir dir(appDir);
        dir.cdUp();
        appDir=dir.path();
    }
    QDir::setCurrent(appDir);

    QDir dConfig(QDir::currentPath()+"/Config");

    if (dConfig.exists())
    {
        //写入update
        QSettings qSet(QDir::currentPath()+"/Config/update.ini", QSettings::IniFormat);
        qSet.setIniCodec("utf-8");

        qSet.setValue("Current/Name", QString(APP_NAME));
        qSet.setValue("Current/Edition", QString(APP_EDITION));
        qSet.setValue("Current/TeamWeb", "https://github.com/ltofuy/DDJM");
        qSet.setValue("Current/Version", QString(APP_VERSION));
        qSet.setValue("Current/TimeStamp", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        qSet.sync();
    }

    //OSOperationWin osWin;
    //qDebug()<<osWin.getCurrentWindowsUsername();


    QFont f("Arial");
    f.setPixelSize(16);
    qApp->setFont(f);

    MainWindow w;
    w.show();
    return a.exec();
}
