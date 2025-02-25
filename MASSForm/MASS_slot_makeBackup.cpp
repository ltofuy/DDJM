#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::makeBackup()
{
    QString content="";

    //制作存档保存;
    if (QSysInfo::productType() != "windows")
    {
        //Linux下获取用于名
        QString userName = qgetenv("USER");

        // /home/[user]/.renpy/Monika After Story

        content += "Wait for a function update for non-windows platforms";
        if (isSilentBackup == false)
        {
            QMessageBox::information(NULL, "", content, QMessageBox::Ok);
        }
        return;
    }

    OSOperationWin osw;
    QString filepath = osw.currentRoamingPath("RenPy/Monika After Story/persistent");
    QFile f(filepath);
    QString str_split="\n";
    if (f.exists())
    {
        QString newPath=QDir::currentPath()+"/Data/persistent_"+QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        newPath = newPath.replace("/", "\\");
        QFile::copy(filepath, newPath);

        if (QFile::exists(newPath))
        {
            content += "The persistent has been recorded from: "+str_split;
            content += filepath.replace("\\", "/") + str_split;
            content += "to: "+str_split;
            content += newPath.replace("\\", "/");
        }
        else {
            content += "Copy failed to: "+str_split;
            content += filepath.replace("\\", "/");
        }
    }
    else {
        content += "Nothing found in: "+str_split;
        content += filepath.replace("\\", "/");
    }
    content += "\n\n";

    //同时备份文件夹
    QString timeStamp=QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    if (f.exists())
    {
        QFileInfo finfo(filepath);
        //获取那个文件夹;
        QDir dir_MAS_persistent = finfo.dir();
        //qDebug()<<dir_MAS_persistent.path();

        //获取备份文件夹
        //记录临时名
        temp_backup_dirname="Monika After Story "+timeStamp;
        QString backupDirPath=QDir::currentPath()+"/Data/Monika After Story "+timeStamp;
        QDir dir_MAS_p_backups(backupDirPath);
        if (!dir_MAS_p_backups.exists(backupDirPath))
        {
            dir_MAS_p_backups.mkpath(backupDirPath);
        }

        //逐个复制
        QFileInfoList original_files = dir_MAS_persistent.entryInfoList();
        //qDebug()<<original_files;

        //处理统一状态, 有一个错误都不行;
        bool isSuccess=true;
        //逐个复制
        for (int i=0;i<original_files.count();++i)
        {
            QString filename = original_files.at(i).fileName();
            //qDebug()<<filename;
            if (filename == "." || filename == "..")
            {
                continue;
            }
            bool b = QFile::copy(original_files.at(i).filePath().replace("\\", "/"), backupDirPath + "/" + filename);
            if (b == false)
            {
                content += tr("COPY persistent ERROR!!!")+"\n";
                content += original_files.at(i).filePath() + "\n\n";
                isSuccess = false;
            }
            else {

            }
        }

        //统一处理
        if (isSuccess == true)
        {
            content += tr("Make backups-folder of persistent for Monika After Story successful")+"\n";
            content += tr("Monika After Story folder saved as")+": "+timeStamp+" "+"in"+" "+"Data";

            //存储时间戳
            QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
            qSet.setIniCodec("utf-8");
            qSet.setValue("Last/persistent_folder_backup", backupDirPath);
            temp_backup_dirpath=backupDirPath;
            qSet.sync();
        }

    }

    if (isSilentBackup==false)
    {
        QMessageBox::information(NULL, "", content, QMessageBox::Ok);
    }
}
