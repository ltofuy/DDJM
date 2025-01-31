#ifndef DDWORDDIALOG_H
#define DDWORDDIALOG_H

#include <QDialog>
#include <QVector>
#include <QTableWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

namespace Ui {
class DDWordDialog;
}

class DDWordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DDWordDialog(QWidget *parent = nullptr);
    ~DDWordDialog();

    QButtonGroup bg_trans_1;
    QButtonGroup bg_trans_2;

    //对指定的table进行显示重置
    void resetTableRowCount(QTableWidget *w, int rowCount);

    //内部存储已经录入的内容
    QStringList savedWordList[2];

    //记录上次存储的模式
    //上次存储的tab个数, 1个还是2个
    int last_count_tab;
    //按照上次存储的1还是2写入当前名以及存储的单词
    QString last_name[2];
    QStringList last_words[2];

public slots:
    //设置词汇
    //只设置1个, 默认是1周目或者Monika
    void setWord(QString cname, QStringList words);
    //设置2个, 为包含二周目的Yuri以及Natsuki情况
    void setWord(QString cname1, QStringList words1, QString cname2, QStringList words2);

    //获取翻译
    void getTranslationAct1(int index);
    void getTranslationAct2(int index);

    //设定检索模式
    void toEnableMatchAct1(bool b);
    void toEnableMatchAct2(bool b);

    //依据text检索原文
    void translateOL(QString text);

    //检索
    void checkAct1();
    void checkAct2();

    void checkAct(QTableWidget *w, bool isRe, QString str_re, int length, QStringList oWords);

    void reset_1();
    void reset_2();

private:
    Ui::DDWordDialog *ui;
};

#endif // DDWORDDIALOG_H
