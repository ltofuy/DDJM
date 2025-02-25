#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::refreshMonikaLove()
{
    QDir d(ui->lineEdit_dir->text());
    if (d.exists() && !ui->lineEdit_dir->text().isEmpty())
    {
        //查找好感度
        QFile f(ui->lineEdit_dir->text()+"/log/aff_log.log");
        if (!f.exists())
        {
            ui->label_monika_love->setText("???");
            return;
        }
        if (f.open(QIODevice::Text|QIODevice::ReadOnly))
        {
            QString content=QString::fromUtf8(f.readAll());
            QStringList list=content.split("\n");

            //qDebug()<<list;

            for (int i=0;i<list.count();++i)
            {
                //反向检索;
                int index=list.count()-1-i;
                QString l=list.at(index);
                l=l.remove(" ");
                if (l.count() == 0)
                {
                    continue;
                }

                QStringList part_list=l.split(":SAVE|");
                if (part_list.count()==2)
                {
                    QString v=QString::number(part_list.at(1).toDouble(), 'f', 2);
                    ui->label_monika_love->setText(v);
                    break;
                }
            }

            f.close();
        }
    }
}

