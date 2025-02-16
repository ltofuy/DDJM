#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::reload()
{
    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");
    QString dirpath=qSet.value("Last/persistent_folder_backup").toString();
    QDir thatDir(dirpath);

    if (dirpath == "" || thatDir.exists(dirpath) == false)
    {
        QMessageBox::information(NULL, tr("No last persistent backup folder"), tr("No last persistent backup folder found"), QMessageBox::Ok);
        return;
    }

    //确认用户真的要覆盖存档
    QString content = tr("You have a backup-archive named:")+"\n";
    content += dirpath + "\n";
    content += tr("Do you still want to recover it to the current")+"?";
    content += tr("Once down, it is hard to restore the lost files to Monika");

    QMessageBox::StandardButton a=QMessageBox::warning(NULL, "WARNING", content, QMessageBox::Yes|QMessageBox::No);
    switch (a) {
    case QMessageBox::Yes:
        break;
    default:
        //退出
        return;
        break;
    }

    //覆盖当前存档, 为避免麻烦也要备份当前的状态
    isSilentBackup = true;
    makeBackup();
    isSilentBackup = false;

    //重新刷回
    OSOperationWin osw;
    QString filepath = osw.currentRoamingPath("RenPy/Monika After Story/persistent");
    QFile f(filepath);
    QDir dir_p=QFileInfo(filepath).dir();
    QString dir_p_path=dir_p.path();
    if (dir_p.exists() && dir_p.dirName()=="Monika After Story")
    {
        //因为已经备份了所以递归删除;
        dir_p.removeRecursively();
    }
    else {
        qDebug()<<"文件夹设置错误";
    }
    if (!dir_p.exists(dir_p_path))
    {
        dir_p.mkpath(dir_p_path);
    }

    content = "";
    bool isSuccess=true;
    QFileInfoList infolist=thatDir.entryInfoList();
    for (int i=0;i<infolist.count();++i)
    {
        QString filename = infolist.at(i).fileName();
        //qDebug()<<filename;
        if (filename == "." || filename == "..")
        {
            continue;
        }

        bool b = QFile::copy(infolist.at(i).filePath(), dir_p_path + "/"+filename);
        if (b == false)
        {
            content += tr("COPY persistent ERROR!!!")+"\n";
            content += infolist.at(i).filePath() + "\n\n";
            isSuccess = false;
        }
    }

    if (isSuccess == true)
    {
        content += tr("Reload persistent folder successfully, you originial persistent folder is now the last backup");
        QMessageBox::information(NULL, "", content, QMessageBox::Ok);
    }
}
