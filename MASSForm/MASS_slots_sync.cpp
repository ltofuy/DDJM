#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::sync()
{
    QString content = tr("Please Select the task you need to perform")+":"+"\n";
    content+="\n";
    content+="1. "+tr("Record")+": "+tr("Make a backup of the current persistent files to the target folder")+".\n";
    content+="2. "+tr("Load")+": "+tr("Recover the persistent files from a valid folder of synchronization")+".\n";

    QMessageBox box;
    box.setText(content);
    box.addButton(tr("Record"), QMessageBox::AcceptRole);
    box.addButton(tr("Load"), QMessageBox::ResetRole);
    box.addButton(tr("Cancel"), QMessageBox::RejectRole);



    //模式已经由a记录了
    int a=box.exec();
    switch (a) {
    case 0:
        //record;
        //qDebug()<<"record";
    {
        //首先备份一次存档, 静默模式
        bool isSSet=isSilentBackup;
        isSilentBackup = true;
        makeBackup();
        isSilentBackup = isSSet;

        //直接获取文件夹
        QString dirpath=QFileDialog::getExistingDirectory();
        if (!dirpath.isEmpty())
        {
            //将Config和存档备份
            //判断目标文件夹已经有config则先删除, 然后复制
            QString configname=QString(APP_NAME)+"_config.ini";
            QString config_current=QDir::currentPath()+"/Config/"+configname;
            QString config_sync_dir=dirpath+"/"+configname;
            if (QFile::exists(config_sync_dir))
            {
                QFile::remove(config_sync_dir);
            }
            QFile::copy(config_current, config_sync_dir);

            //依据记录的临时temp信息, 复制那些文件夹
            bool b=copyDirectory(temp_backup_dirpath, dirpath+"/"+temp_backup_dirname);
            if (b)
            {
                QMessageBox::information(NULL, "", tr("Copy successful"), QMessageBox::Ok);
            }
            else {
                QMessageBox::information(NULL, "", tr("Copy failed"), QMessageBox::Ok);
            }
        }
        else {
            QMessageBox::information(NULL, "", tr("No vaild folder found, operation Cancel"), QMessageBox::Ok);
        }
    }
        break;
    case 1:
        //load;
        //qDebug()<<"load";
    {
        //在目标那里寻找config文件然后读取
        //直接获取文件夹
        QString dirpath=QFileDialog::getExistingDirectory();
        if (!dirpath.isEmpty())
        {
            //将Config和存档备份
            //判断目标文件夹已经有config则先删除, 然后复制
            QString configname=QString(APP_NAME)+"_config.ini";
            QString config_sync_dir=dirpath+"/"+configname;
            QString config_current=QDir::currentPath()+"/Config/"+configname;

            QSettings qSet_sync_dir(config_sync_dir, QSettings::IniFormat);
            qSet_sync_dir.setIniCodec("utf-8");
            QSettings qSet_current(config_current, QSettings::IniFormat);
            qSet_current.setIniCodec("utf-8");

            //只处理Last/persistent_folder_backup项
            //注意, 由于不同电脑的备份文件夹不一样, 因此需要处理这一项的地址
            QString from_dir_original_path=qSet_sync_dir.value("Last/persistent_folder_backup").toString();
            if (from_dir_original_path.isEmpty())
            {
                //说明不存在;
                QMessageBox::information(NULL, "", tr("No valid folder settings, operation cancel"), QMessageBox::Ok);
                return;
            }
            //获取其最后地址必须时间戳相同
            QString that_dir_name=from_dir_original_path.split("/").last();

            //获取其法定地址
            QString that_dir_path_from=dirpath+"/"+that_dir_name;
            QDir thatDir(that_dir_path_from);
            if (!thatDir.exists())
            {
                //说明不存在;
                QMessageBox::information(NULL, "", tr("No valid folder settings, operation cancel"), QMessageBox::Ok);
                return;
            }

            //若存在则复制到本地然后重写config
            bool b=copyDirectory(that_dir_path_from, QDir::currentPath()+"/Data/"+that_dir_name);

            //依据记录的临时temp信息, 复制那些文件夹
            //bool b=copyFileToDirectory(temp_backup_dirpath, dirpath+"/"+temp_backup_dirname);
            if (b)
            {
                //QMessageBox::information(NULL, "", tr("Copy successful"), QMessageBox::Ok);
                //这里复制成功只继续下一步, 新的地址
                qSet_current.setValue("Last/persistent_folder_backup", QDir::currentPath()+"/Data/"+that_dir_name);
                qSet_current.sync();

                //随后立即执行reload
                reload();
            }
            else {
                QMessageBox::information(NULL, "", tr("Copy failed"), QMessageBox::Ok);
            }
        }
        else {
            QMessageBox::information(NULL, "", tr("No vaild folder found, operation Cancel"), QMessageBox::Ok);
        }
    }
        break;
    case 2:
        //cancel;
        //qDebug()<<"cancel";
        return;
        break;
    }


}
