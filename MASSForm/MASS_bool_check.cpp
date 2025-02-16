#include "MASSForm.h"

bool MASSForm::checkProcess(QString exeName)
{
    //获取列表并检查;
    QStringList list = getCurrentProcesses();

    bool found = false;
    for (int i=0;i<list.count();++i)
    {
        QString l=list.at(i);
        if (l.contains(exeName, Qt::CaseInsensitive))
        {
            //tips(tr("Program")+" "+exeName+" "+tr("is still running")+".");
            found = true;
            break;
        }
    }

    return found;
}
