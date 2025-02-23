#ifndef EZ_WRITE_LOG_H
#define EZ_WRITE_LOG_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>

void writeLog(QString content);

QString fileMD5(QString path);

bool copyFileToDirectory(QString filePath, QString destinationDir);


#endif // EZ_WRITE_LOG_H
