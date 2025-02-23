#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

void DDWordDialog::setWord(QString cname, QStringList words)
{
    //仅显示Tab-1
    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, false);

    //重新设置tab_name
    ui->tabWidget->setTabText(0, "Act-1");
    ui->tabWidget->setTabText(1, "Act-2");

    if (cname == "Monika")
    {
        ui->label_icon->setPixmap(QPixmap(":/Resource/M-mini.png"));
        ui->label_icon->setScaledContents(true);

        QStringList newWords=words;
        newWords.sort();
        resetTableRowCount(ui->tableWidget_1, newWords.count());
        for (int i=0;i<newWords.count();++i)
        {
            ui->tableWidget_1->item(i, 0)->setText(newWords.at(i));
        }

        ui->tabWidget->setTabText(0, "Monika After Story");
        ui->tabWidget->setTabText(1, "Doki-Doki Literature Club");

        savedWordList[0]=newWords;
    }

    QVector<QPair<QString, QString>> otherGirls;
    otherGirls<<QPair<QString, QString>("Sayori", ":/Resource/S-mini.png");
    otherGirls<<QPair<QString, QString>("Yuri", ":/Resource/Y-mini.png");
    otherGirls<<QPair<QString, QString>("Natsuki", ":/Resource/N-mini.png");

    for (int i=0;i<otherGirls.count();++i)
    {
        if (cname == otherGirls.at(i).first)
        {
            ui->label_icon->setPixmap(QPixmap(otherGirls.at(i).second));
            ui->label_icon->setScaledContents(true);

            QStringList newWords=words;
            newWords.sort();
            resetTableRowCount(ui->tableWidget_1, newWords.count());
            for (int j=0;j<newWords.count();++j)
            {
                ui->tableWidget_1->item(j, 0)->setText(newWords.at(j));
            }

            savedWordList[0]=newWords;
        }
    }
}

void DDWordDialog::setWord(QString cname1, QStringList words1, QString cname2, QStringList words2)
{
    //若选择为Monika或Sayori, 则退回setWord(a, b)
    if (cname1.toLower().contains("monika") || cname1.toLower().contains("sayori"))
    {
        QString name=cname1.split("-").first();
        setWord(name, words1);
        return;
    }

    //先显示Tab-1和2,
    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, true);

    //重新设置tab_name
    ui->tabWidget->setTabText(0, "Act-1");
    ui->tabWidget->setTabText(1, "Act-2");

    //仅处理Natsuki以及Yuri的情况
    QVector<QPair<QString, QString>> otherGirls;
    otherGirls<<QPair<QString, QString>("Yuri", ":/Resource/Y-mini.png");
    otherGirls<<QPair<QString, QString>("Natsuki", ":/Resource/N-mini.png");

    for (int i=0;i<otherGirls.count();++i)
    {
        if (cname1.indexOf(otherGirls.at(i).first)!=-1 && cname2.indexOf(otherGirls.at(i).first)!=-1)
        {
            ui->label_icon->setPixmap(QPixmap(otherGirls.at(i).second));
            ui->label_icon->setScaledContents(true);

            //先处理Act-1
            QStringList newWords=words1;
            newWords.sort();
            resetTableRowCount(ui->tableWidget_1, newWords.count());
            for (int j=0;j<newWords.count();++j)
            {
                ui->tableWidget_1->item(j, 0)->setText(newWords.at(j));
            }
            savedWordList[0]=newWords;

            //再处理Act-2
            newWords=words2;
            newWords.sort();
            resetTableRowCount(ui->tableWidget_2, newWords.count());
            for (int j=0;j<newWords.count();++j)
            {
                ui->tableWidget_2->item(j, 0)->setText(newWords.at(j));
            }
            savedWordList[1]=newWords;
        }
    }
}
