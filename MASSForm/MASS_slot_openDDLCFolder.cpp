#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::openDDLCFolder()
{
    QDesktopServices::openUrl(QUrl(ui->lineEdit_dir->text()));
}
