#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::buttonOperationGiftSended(int a)
{
    //重新求解
    int index_type = a/maxRowCount;
    int index_row = a%maxRowCount;

    //获取那个table
    QTableWidget *w=wList.data()[index_type];

    //获取指定的row所对应的名称和code
    QString name = w->item(index_row, 0)->text();
    QString code = w->item(index_row, 1)->text();

    //发射命令
    toSendGift(ui->lineEdit_dir->text(), name, code);
}

void MASSForm::buttonOperation(int a)
{
    /*
    connect(ui->pushButton_find, SIGNAL(clicked()), this, SLOT(findDir()));
    connect(ui->pushButton_monika_love, SIGNAL(clicked()), this, SLOT(refreshMonikaLove()));
    connect(ui->pushButton_MTG, SIGNAL(clicked()), M2G, SLOT(show()));
    connect(ui->pushButton_visit_Monika, SIGNAL(clicked()), this, SLOT(visitMonika()));
    connect(ui->pushButton_backups, SIGNAL(clicked()), this, SLOT(makeBackup()));
    connect(ui->pushButton_reload, SIGNAL(clicked()), this, SLOT(reload()));
    connect(ui->pushButton_open_folder, SIGNAL(clicked()), this, SLOT(openDDLCFolder()));
    */
    switch (a) {
    case 0:
        //设置文件夹
        findDir();
        break;
    case 1:
        //刷新monika好感
        refreshMonikaLove();
        break;
    case 2:
        //显示MTG
        M2G->show();
        break;
    case 3:
        //拜访她
        visitMonika();
        break;
    case 4:
        //备份存档
        makeBackup();
        break;
    case 5:
        //重载存档
        reload();
        break;
    case 6:
        //打开DDLC文件夹
        openDDLCFolder();
        break;
    case 7:
        //同步
        sync();
        break;
    }
}

/*
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
*/
