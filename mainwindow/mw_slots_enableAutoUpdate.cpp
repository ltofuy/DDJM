#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::enableAutoUpdate(bool b)
{
    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    qSet.setValue("Update/Auto", b);
    qSet.sync();

    //若是立即设置为true, 则执行一次更新检查
    if (b == true)
    {
        autoCheckUpdate();
    }
}
