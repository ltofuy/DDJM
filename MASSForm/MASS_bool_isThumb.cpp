#include "MASSForm.h"
#include "ui_MASSForm.h"

bool MASSForm::isThumb(QString typeName, QFileInfo info, QString codeO, QString code, int fileCount)
{
    //获取part与partList, 其基于baseName进行分解
    QString part=info.baseName().toLower().replace("_", "").replace("-", "");
    QStringList partList=info.baseName().toLower().replace("_", "-").split("-");

    if (typeName == "cloth")
    {
        //按照衣服进行处理;
        if (part.contains(code.toLower())
                ||fileCount==1
                ||part.contains(typeName))
        {
            return true;
        }
        else {
            return false;
        }
    }

    if (typeName == "ribbon")
    {
        //发带则复杂一些
        if (part.contains(code.toLower())
                ||fileCount==1
                //||part.contains(typeName)
                ||part.startsWith(codeO.left(qMin(3, codeO.count())))
                ||(codeO.startsWith(partList.last()) || codeO.endsWith(partList.last()))
                ||part.contains(codeO))
        {
            return true;
        }
        else {
            return false;
        }
    }

    if (typeName == "hairclip" || typeName == "earring"|| typeName == "choker")
    {
        //按照衣服进行处理;
        if (part.contains(code.toLower())
                ||fileCount==1
                ||part.contains(typeName)
                ||part.startsWith(codeO.left(qMin(3, codeO.count()))))
        {
            return true;
        }
        else {
            return false;
        }
    }

    //默认返还false
    return false;
}
