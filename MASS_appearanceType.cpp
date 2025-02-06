#include "MASSForm.h"
#include "ui_MASSForm.h"

int MASSForm::appearanceType(QDir dir)
{
    QFileInfoList infoList=dir.entryInfoList(QDir::Dirs);
    for (int i=0;i<infoList.count();++i)
    {
        QFileInfo info=infoList.at(i);
        QString l=info.baseName();
        if (l.contains("c"))
        {
            //clothe
            return 0;
        }
        else if (l.contains("a") && info.path().contains("earring"))
        {
            //耳环
            return 3;
        }
        else if (l.contains("a") && info.path().contains("ribbon")){
            //发带
            return 1;
        }
        else if (l.contains("a") && info.path().contains("hairclip")){
            //发卡
            return 2;
        }
    }

    //其它礼物
    return 4;
}
