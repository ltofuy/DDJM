#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

void DDWordDialog::checkAct1()
{
    QTableWidget *w=ui->tableWidget_1;
    //是否启动检索匹配
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
    //暂时不启用这部分内容, 以避免重置失效
    /*
    if (isRE == false && length == 0)
    {
        QString content=tr("You need to first determine a search mode, such as searching based on the expression or searching based on word length. If the word length is set to 0, it means all words will be displayed.");
        QMessageBox::warning(NULL, "", content, QMessageBox::Ok);
        return;
    }
    */

    //首先, 这个table全部显示
    for (int i=0;i<w->rowCount();++i)
    {
        w->setRowHidden(i, false);
    }

    //处理Act
    //[1] 使用检索匹配模式处理
    if (isRE==true)
    {
        //那么使用匹配规则进行处理;
        for (int i=0;i<w->rowCount();++i)
        {
            if (i<oWords.count())
            {
                //显示 已经整体显示
                //w->setRowHidden(i, false);
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
            else {
                w->setRowHidden(i, true);
            }
        }
    }
    //[2] 仅使用长度匹配
    else {
        //使用长度匹配
        for (int i=0;i<w->rowCount();++i)
        {
            if (i<oWords.count())
            {
                w->setRowHidden(i, false);
                //处理是否显示
                if (length<=0 || w->item(i, 0)->text().remove(" ").length() == length)
                {
                    //length<=0表示全显示, 长度匹配也表示显示, 仅这两种情况显示
                    //注意因为一开始已经显示了;
                    //w->setRowHidden(i, false);
                }
                else {
                    w->setRowHidden(i, true);
                }
            }
            else {
                w->setRowHidden(i, true);
            }
        }
    }
}

