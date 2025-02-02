#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::visitMonika()
{
    QString path=ui->lineEdit_dir->text()+"/DDLC";
    if (QSysInfo::productType()=="windows")
    {
        path += ".exe";
    }
    else {
        path += ".sh";
    }

    //确保文件必须存在
    if (!QFile::exists(path))
    {
        QMessageBox::warning(NULL, "", tr("Program lost!"), QMessageBox::Ok);
        return;
    }


    //确保进程里不要有重复
    if (checkProcess("DDLC.exe") == true)
    {
        QMessageBox::warning(NULL, "", tr("A DDLC is running now, the new starting has been terminated!"), QMessageBox::Ok);
        return;
    }

    //qDebug()<<path;

    QProcess p;
    p.setProgram(path);
    p.startDetached();
}
