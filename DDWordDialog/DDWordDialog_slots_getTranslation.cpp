#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

void DDWordDialog::getTranslationAct1(int number)
{
    QTableWidgetItem *item=ui->tableWidget_1->item(number, 0);
    if (item == nullptr)
    {
        return;
    }

    translateOL(item->text());
}

void DDWordDialog::getTranslationAct2(int number)
{
    QTableWidgetItem *item=ui->tableWidget_2->item(number, 0);
    if (item == nullptr)
    {
        return;
    }

    translateOL(item->text());
}
