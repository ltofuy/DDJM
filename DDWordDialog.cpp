#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

DDWordDialog::DDWordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DDWordDialog)
{
    ui->setupUi(this);

    setFixedSize(size());

    //首先初始化widget-1和2
    QVector<QTableWidget*> tables;
    tables<<ui->tableWidget_1;
    tables<<ui->tableWidget_2;
    QVector<QButtonGroup*> bgGs;
    bgGs<<&bg_trans_1;
    bgGs<<&bg_trans_2;
    int columnCount=2;
    int rowCount=256;
    int wordWidth=300;
    for (int i=0;i<tables.count();++i)
    {
        QTableWidget *w=tables.data()[i];
        //w->
        w->setColumnCount(columnCount);
        w->setRowCount(rowCount);
        w->setColumnWidth(0, wordWidth);
        for (int j=0;j<rowCount;++j)
        {
            for (int k=0;k<columnCount-1;++k)
            {
                QTableWidgetItem *item=w->item(j, k);
                if (item==nullptr)
                {
                    w->setItem(j, k, new QTableWidgetItem);
                }
                QPushButton *b=new QPushButton;
                b->setText("Translate");
                w->setCellWidget(j, columnCount-1, b);
                bgGs.data()[i]->addButton(b, j);
            }
        }
    }


    savedWordList[0].clear();
    savedWordList[1].clear();

    //初始时lineEdit不可用
    ui->lineEdit_re_1->setEnabled(false);
    ui->lineEdit_re_2->setEnabled(false);
    ui->spinBox_1->setEnabled(false);
    ui->spinBox_2->setEnabled(false);

    connect(&bg_trans_1, SIGNAL(buttonClicked(int)), this, SLOT(getTranslationAct1(int)));
    connect(&bg_trans_2, SIGNAL(buttonClicked(int)), this, SLOT(getTranslationAct2(int)));

    connect(ui->checkBox_re_1, SIGNAL(clicked(bool)), this, SLOT(toEnableMatchAct1(bool)));
    connect(ui->checkBox_re_2, SIGNAL(clicked(bool)), this, SLOT(toEnableMatchAct2(bool)));

    connect(ui->pushButton_check_1, SIGNAL(clicked()), this, SLOT(checkAct1()));
    connect(ui->pushButton_check_2, SIGNAL(clicked()), this, SLOT(checkAct2()));
}

DDWordDialog::~DDWordDialog()
{
    delete ui;
}

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

void DDWordDialog::translateOL(QString text)
{
    QString code="https://cn.bing.com/translator?ref=TThis&text="+text.remove(" ")+"&from=en&to=zh-Hans";
    QDesktopServices::openUrl(QUrl(code));
}

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

void DDWordDialog::toEnableMatchAct1(bool b)
{
    if (b==true)
    {
        ui->lineEdit_re_1->setEnabled(true);
        ui->spinBox_1->setEnabled(false);
    }
    else {
        ui->lineEdit_re_1->setEnabled(false);
        ui->spinBox_1->setEnabled(true);
    }
}

void DDWordDialog::toEnableMatchAct2(bool b)
{
    if (b==true)
    {
        ui->lineEdit_re_2->setEnabled(true);
        ui->spinBox_2->setEnabled(false);
    }
    else {
        ui->lineEdit_re_2->setEnabled(false);
        ui->spinBox_2->setEnabled(true);
    }
}

void DDWordDialog::checkAct1()
{
    QTableWidget *w=ui->tableWidget_1;
    bool isRE=ui->checkBox_re_1->isChecked();
    QString str_re=ui->lineEdit_re_1->text();
    int length=ui->spinBox_1->value();
    QStringList oWords=savedWordList[0];

    checkAct(w, isRE, str_re, length, oWords);
}

void DDWordDialog::checkAct2()
{
    QTableWidget *w=ui->tableWidget_2;
    bool isRE=ui->checkBox_re_2->isChecked();
    QString str_re=ui->lineEdit_re_2->text();
    int length=ui->spinBox_2->value();
    QStringList oWords=savedWordList[1];

    checkAct(w, isRE, str_re, length, oWords);
}

void DDWordDialog::checkAct(QTableWidget *w, bool isRE, QString str_re, int length, QStringList oWords)
{
    //处理Act
    if (isRE==true)
    {
        //那么使用匹配规则进行处理;
        for (int i=0;i<w->rowCount();++i)
        {
            if (w->isRowHidden(i))
            {
                //隐藏了就不用管了;
                break;
            }
            else {
                //进行处理
                QString word=w->item(i, 0)->text();
                if (word.length()==str_re.length())
                {
                    //确保长度相同以进一步匹配;
                    bool isPossible=true;
                    for (int j=0;j<str_re.count();++j)
                    {
                        //检查不带*的位置是否相同, 全部相同才进入下一步;
                        if (str_re.at(j)!="*")
                        {
                            //处理;
                            if (word.at(j) != str_re.at(j))
                            {
                                //一定不匹配
                                isPossible=false;
                                break;
                            }
                        }
                    }

                    //若可能匹配则保留, 否则隐藏本行;
                    w->setRowHidden(i, !isPossible);
                }
                else {
                    w->setRowHidden(i, true);
                }
            }
        }
    }
    else {
        //使用长度匹配
        //若value=0, 则重置为初始
        if (length<=0)
        {
            for (int i=0;i<w->rowCount();++i)
            {
                if (i<oWords.count())
                {
                    w->setRowHidden(i, false);
                }
                else {
                    w->setRowHidden(i, true);
                }
            }
        }
        else{
            //检索;
            for (int i=0;i<w->rowCount();++i)
            {
                if (w->isRowHidden(i))
                {
                    //隐藏了就不用管了;
                    break;
                }
                else {
                    if (w->item(i, 0)->text().remove(" ").length() != length)
                    {
                        //隐藏
                    }
                }
            }
        }

    }
}
