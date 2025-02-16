#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::refreshGiftStatus(QVector<QStringList> giftSettings, QString configpath, QTableWidget *w)
{
    QSettings qSet(configpath, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    int index=wList.indexOf(w);
    QString sub="";
    switch (index) {
    case 0:
        sub="cloth";
        break;
    case 1:
        sub="ribbon";
        break;
    case 2:
        sub="hairclip";
        break;
    case 3:
        sub="earring";
        break;
    case 4:
        sub="choker";
        break;
    default:
        sub="";
        break;
    }


    for (int i=0;i<w->rowCount();++i)
    {
        if (i<giftSettings.count())
        {

            //显示
            QString codeO=giftSettings.at(i).at(1);
            QString code=codeO;
            w->setRowHidden(i, false);
            w->item(i, 0)->setText(giftSettings.at(i).at(0));
            w->item(i, 1)->setText(code);

            //查找赠送情况
            int count = qSet.value("Count/"+code).toInt();

            w->item(i, 2)->setText(QString::number(count));

            //处理code 礼物码
            code = code.remove(sub+"es");
            code = code.remove(sub+"s");
            code = code.remove(sub);

            /*
            //抓thumb
            QString thatPath="";
            QDir d;
            for (int j=0; j<giftFileInMods.count();++j)
            {
                if (giftFileInMods.at(j).baseName()==codeO)
                {
                    thatPath=giftFileInMods.at(j).filePath();
                    d = giftFileInMods.at(j).dir();
                    d.cdUp();
                    break;
                }
            }
            if (thatPath != "")
            {
                d = QDir(d.path()+"/mod_assets/thumbs");
                QFileInfoList pngs=d.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
                for (int k=0;k<pngs.count();++k)
                {
                    QString part=pngs.at(k).baseName().toLower().replace("_", "").replace("-", "");
                    QStringList partList=pngs.at(k).baseName().toLower().replace("_", "-").split("-");
                    if (isThumb(sub, pngs.at(k), codeO, code, pngs.count()))
                    {
                        //载入icon
                        QLabel *ll=allLabels.data()[index].data()[i];
                        ll->setPixmap(QPixmap(pngs.at(k).filePath()));
                        int height = w->rowHeight(i);
                        ll->setFixedSize(QSize(height, height));
                        ll->setScaledContents(true);
                        break;
                    }
                }
            }
            */

            //使用新的实现
            QString thatGiftCode=giftSettings.at(i).at(1);
            //检索
            for (int j=0;j<giftAllInfoList.count();++j)
            {
                if (giftAllInfoList.at(j).at(0) == thatGiftCode)
                {
                    //说明找到了;
                    //处理
                    QString thatGroup=giftAllInfoList.at(j).at(1);
                    QString thatFileName=giftAllInfoList.at(j).at(2);
                    //qDebug()<<thatGiftCode<<thatGroup<<thatFileName;
                    if (thatGiftCode=="bluebunnyscrunchie")
                    {
                        qDebug()<<thatGiftCode<<thatGroup<<thatFileName;
                    }
                    //依据thatFileName检索thumb
                    for (int k=0;k<targetsAllInfoList.count();++k)
                    {
                        if (targetsAllInfoList.at(k).baseName().contains(thatFileName)
                                && targetsAllInfoList.at(k).filePath().endsWith(".png")
                                && targetsAllInfoList.at(k).filePath().contains("/thumbs/")
                                && isMatched(thatGroup, sub)
                                )
                        {
                            //处理
                            //qDebug()<<targetsAllInfoList.at(k).filePath()<<thatFileName;
                            //载入icon
                            QLabel *ll=allLabels.data()[index].data()[i];
                            ll->setPixmap(QPixmap(targetsAllInfoList.at(k).filePath()));
                            int height = w->rowHeight(i);
                            ll->setFixedSize(QSize(height, height));
                            ll->setScaledContents(true);
                            break;
                        }
                    }

                    break;
                }
            }
            //旧的实现被跳过
            continue;
        }
        else {
            //隐藏吧
            w->setRowHidden(i, true);
        }
    }
}
