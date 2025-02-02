#ifndef OSOPERATIONWIN_H
#define OSOPERATIONWIN_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

class OSOperationWin
{
public:
    OSOperationWin();

    QString getCurrentWindowsUsername();

    QString getCurrentWindowsLocalUsername();

    QString currentRoamingPath(QString persistentName);
};

#endif // OSOPERATIONWIN_H
