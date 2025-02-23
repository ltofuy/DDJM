#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::download(QString url, QString targetFilepath)
{
    if (isCheckingDownload == true)
    {
        QString content=tr("There is already a downloading task now");
        QMessageBox::warning(NULL, "", content, QMessageBox::Ok);
        return;
    }

    //说明, downloadkit的参数对于github有特殊处理
    //一般参数为 url=>filepath
    //1 url
    //2 下载到本地的地址, 这是一个文件地址, 最好为相对地址

    //我们在下载中不会改变文件名, 因此最终的文件名取决于url
    QString filename = url.split("/").last();

    QProcess p;
    QString suffix="";
    if (QSysInfo::productType()=="windows")
    {
        suffix=".exe";
    }
    p.startDetached("./bin/DownloadKit"+suffix, QStringList{url, targetFilepath});

    if (QFile::exists("./log/download_log.txt"))
    {
        QFile::remove("./log/download_log.txt");
    }

    //然后针对targetFilepath进行扫描监视
    isCheckingDownload = true;
    checkingDownloadCurrent = 0;
    DownloadKit_taskName = filename;
    QTimer::singleShot(checkingDownloadTimeStep*4, this, SLOT(checkingDownloadKitWork()));
}

void MainWindow::checkingDownloadKitWork()
{
    QFile f("./log/download_log.txt");
    QStringList contentlist;
    if (f.open(QIODevice::Text|QIODevice::ReadOnly))
    {
        contentlist =QString::fromUtf8(f.readAll()).split("\n");
        f.close();
    }

    qDebug()<<"执行了监视"<<DownloadKit_taskName;

    //获取当前时间戳
    QDateTime currentTime = QDateTime::currentDateTime();

    //倒序检索内容
    bool isFound = false;
    for (int i=0;i<contentlist.count();++i)
    {
        int index=contentlist.count()-i-1;

        QString l=contentlist.at(index);

        if (l.contains(DownloadKit_taskName))
        {
            //找到了
            //判断
            isFound = true;
            if (l.contains("文件成功下载到"))
            {
                //说明已经完成
                isCheckingDownload = false;
                QMessageBox::information(NULL, "",
                                         tr("Downloading finished!")+"\n"+DownloadKit_taskName,
                                         QMessageBox::Ok);
                return;
            }
            else {
                //说明已经开始
                break;
            }
        }
    }

    //次数加1
    checkingDownloadCurrent ++;

    //若判定完未找到, 则可能程序有问题
    if (isFound == false || checkingDownloadCurrent>=checkingDownloadMax)
    {
        isCheckingDownload = false;
        QMessageBox::information(NULL, "",
                                 tr("Something wrong for network, downloading is missing"), QMessageBox::Ok);
    }
    else {
        //继续查询
        QTimer::singleShot(checkingDownloadTimeStep, this, SLOT(checkingDownloadKitWork()));
    }
}
