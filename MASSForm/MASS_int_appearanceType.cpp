#include "MASSForm.h"
#include "ui_MASSForm.h"

int MASSForm::appearanceType(QDir dir)
{
    QFileInfoList infoList=dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for (int i=0;i<infoList.count();++i)
    {
        QFileInfo info=infoList.at(i);
        //qDebug()<<info.filePath()<<info.baseName()<<info.path();
        QString l=info.baseName();
        QString pathlow=info.path().toLower();
        if (l.contains("c"))
        {
            //clothe
            return 0;
        }
        else if ((l.contains("a") && pathlow.contains("ribbon"))
                 || (l.contains("a") && pathlow.contains("bow"))
                 ){
            //发带
            return 1;
        }
        else if (l.contains("a") && pathlow.contains("hairclip")){
            //发卡
            return 2;
        }
        else if (l.contains("a") && pathlow.contains("earring"))
        {
            //耳环
            return 3;
        }
        else if (l.contains("a") && pathlow.contains("choker"))
        {
            //耳环
            return 4;
        }
    }

    //其它礼物现在是5
    return 5;
}
