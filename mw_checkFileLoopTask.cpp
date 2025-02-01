#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::checkFileLoopTask()
{
    qDebug()<<"执行了1次checkFileLoopTask";
    tryLinkCount ++;

    if (tryLinkCount >= tryLinkMaxCount)
    {
        //已达到最大尝试;
        isInCheckLoop = false;
        checkLoop.quit();

        tryLinkCount = 0;

        qDebug()<<"达到最大尝试次数";
    }

    if (isInCheckLoop == true)
    {
        //检查指定文件, 若存在则跳出, 否则继续发送检查命令
        if (QFile::exists(checkFilePath))
        {
            isInCheckLoop = false;
            checkLoop.quit();
            qDebug()<<"文件已经存在, 退出等待loop";
        }
        else {
            //继续检查
            qDebug()<<"再次准备执行checkFileLoopTask";
            QTimer::singleShot(5000, this, SLOT(checkFileLoopTask()));
        }

    }
}
