#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::createDir(QString p)
{
    QDir d(p);
    if (!d.exists())
    {
        d.mkpath(p);
    }
}
