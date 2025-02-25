#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::findDir()
{
    QString fdpath=QFileDialog::getExistingDirectory(NULL, "Select DDLC Folder", QDir::currentPath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if (!fdpath.isEmpty())
    {
        ui->lineEdit_dir->setText(fdpath);
        QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
        qSet.setIniCodec("utf-8");

        qSet.setValue("ID/DDLC_path", fdpath);
        qSet.sync();
    }
}
