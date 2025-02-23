#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::clearDir(QString p)
{
    QDir dir(p);
        // 检查目录是否存在
        if (!dir.exists()) {
            qWarning("指定的目录不存在: %s", qPrintable(p));
            return;
        }
        // 获取目录中的所有文件和子目录
        QFileInfoList fileList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
        // 遍历文件和子目录，删除它们
        for (const QFileInfo &fileInfo : fileList) {
            if (fileInfo.isDir()) {
                // 如果是目录，递归删除
                QDir subDir(fileInfo.absoluteFilePath());
                subDir.removeRecursively();
            } else {
                // 如果是文件，直接删除
                QFile::remove(fileInfo.absoluteFilePath());
            }
       }
}
