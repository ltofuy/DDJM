#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

void DDWordDialog::toEnableMatchAct1(bool b)
{
    if (b==true)
    {
        ui->lineEdit_re_1->setEnabled(true);
        ui->spinBox_1->setEnabled(false);
        ui->checkBox_re_1->setStyleSheet("color:red");
    }
    else {
        ui->lineEdit_re_1->setEnabled(false);
        ui->spinBox_1->setEnabled(true);
        ui->checkBox_re_1->setStyleSheet("color:gray");
    }
}

void DDWordDialog::toEnableMatchAct2(bool b)
{
    if (b==true)
    {
        ui->lineEdit_re_2->setEnabled(true);
        ui->spinBox_2->setEnabled(false);
        ui->checkBox_re_2->setStyleSheet("color:red");
    }
    else {
        ui->lineEdit_re_2->setEnabled(false);
        ui->spinBox_2->setEnabled(true);
        ui->checkBox_re_2->setStyleSheet("color:gray");
    }
}
