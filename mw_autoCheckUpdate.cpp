#include "mainwindow.h"
#include "ui_mainwindow.h"


//本来只想开一个小坑, 没想到给自己挖了个大坑ε=(´ο｀*)))唉
//但考虑到是为了Monika那算了~无妨
void MainWindow::autoCheckUpdate()
{
    clearDir(QDir::currentPath()+"/TEMP");

    checkFilePath = QDir::currentPath()+"/TEMP/update.ini";
    QSettings cSet(QDir::currentPath()+"/Config/update.ini", QSettings::IniFormat);
    cSet.setIniCodec("utf-8");

    //检查更新组件是否存在? 他们应当位于bin下
    QStringList kitInBin=QStringList{"DownloadKit", "PZip", "EZAutoUpdate"};
    QString workStation="win";

    //windows
    if (QSysInfo::productType()=="windows")
    {
        workStation = "win";

        //下载latest-tags文件, 以确认是否包含
        //设置项目的update.ini地址
        QString updateIniInGithub="https://github.com/ltofuy/DDJM/releases/download/latest/update.ini";

        bool isKitExistList[kitInBin.count()];
        for (int i=0;i<kitInBin.count();++i)
        {
            QString path=QDir::currentPath()+"/bin/"+kitInBin.at(i)+".exe";
            isKitExistList[i] = QFile::exists(path);

            //重置kitInBin组件地址
            kitInBin.replace(i, path);

            if (isKitExistList[i] == false)
            {
                //组件不足退出, 不需要返还内容
                writeLog(QString("Kit")+ " " +kitInBin.at(i)+ " "+"is lost");
                return;
            }
        }

        //设置TEMP文件夹
        QDir dir(QDir::currentPath()+"/TEMP");
        if (!dir.exists(QDir::currentPath()+"/TEMP"))
        {
            dir.mkpath(QDir::currentPath()+"/TEMP");
        }

        //依据不动情况来判断
        //常规
        //使用DownloadKit下载ini然后解析
        QProcess p;
        p.setProgram(QString(QDir::currentPath()+"/bin/DownloadKit.exe").replace("/", "\\"));

        p.setArguments(QStringList{updateIniInGithub, QDir::currentPath()+"/TEMP/update.ini"});
        //因为是start, 所以下载后会阻塞, 随后会开始进行处理
        p.startDetached();
        p.waitForStarted();
        p.waitForFinished();

        //startDetached
        //不再阻塞, 但是在这里增加loop, 检查直至循环完成
        isInCheckLoop = true;
        checkFileLoopTask();
        checkLoop.exec();

        writeLog("DownloadKit started in bin");
        writeLog(QString(QDir::currentPath()+"/bin/DownloadKit.exe").replace("/", "\\"));
        writeLog(updateIniInGithub);
        writeLog(QDir::currentPath()+"/TEMP/update.ini");
    }

    QFile f(QDir::currentPath()+"/TEMP/update.ini");
    if (f.exists())
    {
        //说明网络正常可以进行执行
        //比对以询问用户是否需要执行
        QSettings qSet(QDir::currentPath()+"/TEMP/update.ini", QSettings::IniFormat);
        qSet.setIniCodec("utf-8");

        QString thatUrlDirPath=qSet.value("Current/TeamWeb").toString();
        if (qSet.value("Current/Name") == QString(APP_NAME) && (qSet.value("Current/Edition") != QString(APP_EDITION) || qSet.value("Current/Version") != QString(APP_VERSION)) )
        {
            //需要更新
            QString content = tr("There is a new version of DDJM")+": \n";
            content += "Version: "+qSet.value("Current/Version").toString()+"\n";
            content += "Edition: "+qSet.value("Current/Edition").toString()+"\n";
            content += tr("Do you want to update it right now")+"?";
            QMessageBox::StandardButton a=QMessageBox::information(NULL, tr("Update"), content, QMessageBox::Yes|QMessageBox::No);
            if (a == QMessageBox::Yes)
            {
                //将各个组件复制到Update目录下再执行
                createDir(QDir::currentPath()+"/Update");
                for (int i=0;i<kitInBin.count();++i)
                {
                    copyFileToDirectory(kitInBin.at(i), QDir::currentPath()+"/Update");
                }

                //只有到这里才执行更新逻辑
                QProcess p;
                //p.setProgram("cmd");
                //p.startDetached()
                //p.setProgram(QDir::currentPath()+"/Update/EZAutoUpdate.exe");
                QString kitpath=QDir::currentPath()+"/Update/EZAutoUpdate.exe";
                QString urlpath=thatUrlDirPath+"/"+QString(APP_NAME)+"_x64_"+workStation+"_latest.zip";
                //p.setArguments(QStringList{QDir::currentPath()+"/Update/EZAutoUpdate.exe", thatUrlDirPath+"/"+QString(APP_NAME)+"_x64_"+workStation+"_latest.zip"});

                //cSet.setValue("Current/Remote_zip", urlpath);
                //cSet
                //cSet.sync();



                //qDebug()<<kitpath;
                //qDebug()<<urlpath;

                /*
                QFile f(QDir::currentPath()+"/run.cmd");
                if (f.open(QIODevice::Text|QIODevice::WriteOnly))
                {
                    QString code=kitpath;
                    code += " ";
                    code += urlpath;
                    f.write(code.toUtf8());
                    f.close();
                }
                */


                //writeLog(tr("EZAutoUpdate started with")+": "+urlpath);

                qApp->quit();
                p.setProgram(kitpath);
                p.setArguments(QStringList()<<urlpath);
                p.startDetached();

                //p.startDetached("start "+QDir::currentPath()+"/run.cmd");



            }
        }
    }
    else {
        return;
    }
}
