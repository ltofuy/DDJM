#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::buttonOperation_clothes(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_clothes->item(a, 0)->text(), ui->tableWidget_clothes->item(a, 1)->text());
}

void MASSForm::buttonOperation_ribbon(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_ribbon->item(a, 0)->text(), ui->tableWidget_ribbon->item(a, 1)->text());
}

void MASSForm::buttonOperation_hairclip(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_hairclip->item(a, 0)->text(), ui->tableWidget_hairclip->item(a, 1)->text());
}

void MASSForm::buttonOperation_earring(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_earring->item(a, 0)->text(), ui->tableWidget_earring->item(a, 1)->text());
}

void MASSForm::buttonOperation_choker(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_choker->item(a, 0)->text(), ui->tableWidget_choker->item(a, 1)->text());
}

void MASSForm::buttonOperation_gifts(int a)
{
    toSendGift(ui->lineEdit_dir->text(), ui->tableWidget_gifts->item(a, 0)->text(), ui->tableWidget_gifts->item(a, 1)->text());
}
