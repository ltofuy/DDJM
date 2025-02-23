#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

DDWordDialog::DDWordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DDWordDialog)
{
    ui->setupUi(this);

    setFixedSize(size());

    last_count_tab = 0;

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
                b->setText(tr("Translate"));
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

    connect(ui->pushButton_reset_1, SIGNAL(clicked()), this, SLOT(reset_1()));
    connect(ui->pushButton_reset_2, SIGNAL(clicked()), this, SLOT(reset_2()));

    //为避免麻烦, 初始时默认启用检索模式
    reset_1();
    reset_2();
}

DDWordDialog::~DDWordDialog()
{
    delete ui;
}


void DDWordDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
        switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
        }
}

