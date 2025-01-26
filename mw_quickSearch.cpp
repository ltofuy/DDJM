#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::quickSearch()
{
    QString word=ui->lineEdit_findword->text().toLower().remove(" ");

    QStringList checkList=QStringList();

    checkList=wordList.getWords("Monika");
    if (checkList.contains(word))
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("For Monika!");
        ui->label_icon_girl->setPixmap(QPixmap(":/Resource/M-mini.png"));
        ui->label_icon_girl->setScaledContents(true);
        return;
    }

    checkList=wordList.getWords("Sayori");
    if (checkList.contains(word))
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("For Sayori!");
        ui->label_icon_girl->setPixmap(QPixmap(":/Resource/S-mini.png"));
        ui->label_icon_girl->setScaledContents(true);

        //Sayori在2周目还可能包含在Yuri或Natsuki之中
        checkList = wordList.getWords("Yuri", 2);
        if (checkList.contains(word))
        {
            ui->plainTextEdit->appendPlainText("Also for Yuri in Act-2!");
        }
        checkList = wordList.getWords("Natsuki", 2);
        if (checkList.contains(word))
        {
            ui->plainTextEdit->appendPlainText("Also for Natsuki in Act-2!");
        }

        return;
    }

    checkList=wordList.getWords("Yuri");
    if (checkList.contains(word))
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("For Yuri!");
        ui->label_icon_girl->setPixmap(QPixmap(":/Resource/Y-mini.png"));
        ui->label_icon_girl->setScaledContents(true);
        return;
    }

    checkList=wordList.getWords("Natsuki");
    if (checkList.contains(word))
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("For Natsuki!");
        ui->label_icon_girl->setPixmap(QPixmap(":/Resource/N-mini.png"));
        ui->label_icon_girl->setScaledContents(true);
        return;
    }

    //最后处理没找到的情况
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("Oops! Nothing found!");
    ui->label_icon_girl->setPixmap(QPixmap(":/Resource/none-icon-mini.png"));
    ui->label_icon_girl->setScaledContents(true);
}
