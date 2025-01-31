#ifndef EZ_WRITE_LOG_H
#define EZ_WRITE_LOG_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QDebug>

void writeLog(QString content);

bool copyFileToDirectory(QString filePath, QString destinationDir);


#endif // EZ_WRITE_LOG_H
