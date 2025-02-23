#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"


void DDWordDialog::resetTableRowCount(QTableWidget *w, int rowCount)
{
    int rc=w->rowCount();
    for (int i=0;i<rc;++i)
    {
        if (i<rowCount)
        {
            w->setRowHidden(i, false);
        }
        else {
            w->setRowHidden(i, true);

        }
        //w->item(i, 0)->setText("");
    }
}

void DDWordDialog::reset_1()
{
    ui->checkBox_re_1->setChecked(false);
    ui->checkBox_re_1->setStyleSheet("color:gray");
    ui->lineEdit_re_1->setEnabled(false);
    ui->spinBox_1->setValue(0);
    ui->spinBox_1->setEnabled(true);
    ui->pushButton_check_1->click();
}

void DDWordDialog::reset_2()
{
    ui->checkBox_re_2->setChecked(false);
    ui->checkBox_re_2->setStyleSheet("color:gray");
    ui->lineEdit_re_2->setEnabled(false);
    ui->spinBox_2->setValue(0);
    ui->spinBox_2->setEnabled(true);
    ui->pushButton_check_2->click();
}
