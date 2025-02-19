#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::refreshGiftStatus(int a)
{
    QSettings qSet(giftStatusConfig, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    if (a<0 || a>= allTypes.count())
    {
        return;
    }

    //抓取allTypes
    QString type = allTypes.at(a);

    //有了types就简单了, 依据已有的结果直接抓取内容
    QVector<QStringList> contents;
    for (int i=0;i<giftAllInfoList.count();++i)
    {
        //判断type是否一致
        if (giftAllInfoList.at(i).at(1) == type)
        {
            //一致才处理;
            contents << giftAllInfoList.at(i);
        }
    }

    //特别处理, 如果type="", 则补充一些默认值
    if (type == "")
    {
        //录入other gifts
        contents<<QStringList{"coffee", "", "", tr("Coffee"), ""};
        contents<<QStringList{"quetzalplushie", "", "", tr("Quetzal Plushie"), ""};
        contents<<QStringList{"promisering", "", "", tr("Promise Ring"), ""};
        contents<<QStringList{"candy", "", "", tr("Candy"), ""};
        contents<<QStringList{"candycorn", "", "", tr("Candycorn"), ""};
        contents<<QStringList{"hotchocolate", "", "", tr("Hot Chocolate"), ""};
        contents<<QStringList{"candycane", "", "", tr("Candycane"), ""};
        contents<<QStringList{"roses", "", "", tr("Roses"), ""};
        contents<<QStringList{"chocolates", "", "", tr("Chocolate"), ""};
        contents<<QStringList{"justmonikathermos", "", "", tr("Thermos Mug"), ""};
        contents<<QStringList{"fudge", "", "", tr("Fudge"), ""};
        contents<<QStringList{"christmascookies", "", "", tr("Christmas Cookies"), ""};
        contents<<QStringList{"cupcake", "", "", tr("Cupcake"), ""};

        //这是1个随机的
        contents<<QStringList{"as_you_write", "", "", tr("random"), ""};
    }

    //特别处理, 如果type="ribbon", 则补充一些基本值
    if (type == "ribbon")
    {
        contents<<QStringList{"blackribbon", "", "", tr("Black Ribbon"), ""};
        contents<<QStringList{"blueribbon", "", "", tr("Blue Ribbon"), ""};
        contents<<QStringList{"darkpurpleribbon", "", "", tr("Dark-Purple Ribbon"), ""};
        contents<<QStringList{"emeraldribbon", "", "", tr("Emerald Ribbon"), ""};
        contents<<QStringList{"grayribbon", "", "", tr("Gray Ribbon"), ""};
        contents<<QStringList{"greenribbon", "", "", tr("Green Ribbon"), ""};
        contents<<QStringList{"lightpurpleribbon", "", "", tr("Light-Purple Ribbon"), ""};
        contents<<QStringList{"peachribbon", "", "", tr("Peach Ribbon"), ""};
        contents<<QStringList{"pinkribbon", "", "", tr("Pink Ribbon"), ""};
        contents<<QStringList{"platinumribbon", "", "", tr("Platinum Ribbon"), ""};
        contents<<QStringList{"redribbon", "", "", tr("Red Ribbon"), ""};
        contents<<QStringList{"sapphireribbon", "", "", tr("Sapphire Ribbon"), ""};
        contents<<QStringList{"silverribbon", "", "", tr("Silver Ribbon"), ""};
        contents<<QStringList{"tealribbon", "", "", tr("Teal Ribbon"), ""};
        contents<<QStringList{"yellowribbon", "", "", tr("Yellow Ribbon"), ""};
        contents<<QStringList{"rubyribbon", "", "", tr("Ruby Ribbon"), ""};
    }

    //获取目标table
    QTableWidget *w=wList.data()[a];
    for (int i=0;i<w->rowCount();++i)
    {
        if (i<contents.count())
        {
            //读取内容
            QString code = contents.at(i).at(0);
            QString group = contents.at(i).at(1);
            QString thumb = contents.at(i).at(2);
            QString display = contents.at(i).at(3);
            QString thumb_path = contents.at(i).at(4);

            if (code == "")
            {
                //也不显示
                w->setRowHidden(i, true);
                continue;
            }

            //0位置放入display
            w->item(i, 0)->setText(display);

            //1位置放入code
            w->item(i, 1)->setText(code);
            if (type == "")
            {
                //解锁
                w->item(i, 1)->setFlags(w->item(i,1)->flags() | Qt::ItemIsEnabled|Qt::ItemIsEditable);
            }

            //2位置放入赠予个数
            //查找赠送情况
            int count = qSet.value("Count/"+code).toInt();
            w->item(i, 2)->setText(QString::number(count));

            //3位置是按钮, 不用处理

            //4位置是thumb
            if (thumb_path != "" && QFile::exists(thumb_path))
            {
                //载入icon
                QLabel *ll=allLabels.data()[a].data()[i];
                ll->setPixmap(QPixmap(thumb_path));
                int height = w->rowHeight(i);
                ll->setFixedSize(QSize(height, height));
                ll->setScaledContents(true);
            }
        }
        else {
            //隐藏吧
            w->setRowHidden(i, true);
        }
    }
}
