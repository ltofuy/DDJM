#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::openDDLCFolder()
{
    // 将路径转换为URL格式，并替换空格为%20
    QString url = QUrl::fromLocalFile(ui->lineEdit_dir->text()).toString(QUrl::FullyEncoded);
    QDesktopServices::openUrl(QUrl(url));
}
