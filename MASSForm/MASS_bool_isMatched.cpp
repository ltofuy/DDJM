#include "MASSForm.h"
#include "ui_MASSForm.h"

bool MASSForm::isMatched(QString modType, QString theType)
{
    QStringList modeTypeList = {"ribbon", "left-hair-clip", "clothes", "earrings", "choker", "left-hair-flower"};
    QStringList theTypeList={"cloth", "ribbon", "hairclip", "earring", "choker", "gift", ""};
    if (theType == "" || theType.contains("other") || theType.contains("gift"))
    {
        //其它处理;
        if (modeTypeList.indexOf(modType) != 5)
        {
            return false;
        }
        else {
            return true;
        }
    }

    //处理其它情况
    if (modType.replace("-", "").toLower().contains(theType))
    {
        return true;
    }

    //其它情况false
    return false;
}
