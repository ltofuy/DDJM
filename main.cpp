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

    //在这里我们使用了Leo-iTech-Community软件包的发行标准, 因此我们使用了一个兼容其对版本信息进行声明的*.ini文件
    //There is an update information generation for a Leo-iTech-Community style of distribution.
    if (dConfig.exists())
    {
        //写入update
        QSettings qSet(QDir::currentPath()+"/Config/update.ini", QSettings::IniFormat);
        qSet.setIniCodec("utf-8");

        qSet.setValue("Current/Name", QString(APP_NAME));
        qSet.setValue("Current/Edition", QString(APP_EDITION));
        qSet.setValue("Current/TeamWeb", QString(TEAM_WEB));
        qSet.setValue("Current/Version", QString(APP_VERSION));
        qSet.setValue("Current/TimeStamp", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        qSet.sync();
    }

    QFont f("Arial");
    f.setPixelSize(16);
    qApp->setFont(f);

    MainWindow w;
    w.show();

    //在显示后处理翻译问题
    w.checkLanguage();

    return a.exec();
}
