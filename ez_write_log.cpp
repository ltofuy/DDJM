#include "ez_write_log.h"

void writeLog(QString content)
{
    QString logDirpath=QDir::currentPath()+"/log";
    QDir dirLog(logDirpath);
    if (!dirLog.exists())
    {
        dirLog.mkpath(logDirpath);
    }

    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QString logFile(logDirpath+"/"+QDateTime::currentDateTime().toString("yyyy-MM-dd")+"_"+QString(APP_NAME)+".log");
    QFile f(logFile);
    if (f.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        f.write(timeStamp.toUtf8()+"\n");
        f.write(content.toUtf8()+"\n");
        f.write("\n");
        f.close();
    }
}


QString fileMD5(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        //qWarning() << "Cannot open file for reading:" << path;
        return QString();
    }
    QCryptographicHash hash(QCryptographicHash::Md5);
    if (!hash.addData(&file)) {
        //qWarning() << "Failed to read file data:" << path;
        return QString();
    }
    return hash.result().toHex();
}

bool copyFileToDirectory(QString filePath, QString destinationDir) {
    // 创建一个QFile对象
    QFile file(filePath);
    // 检查源文件是否存在
    if (!file.exists()) {
        qDebug() << "源文件不存在:" << filePath;
        return false;
    }
    // 创建目标目录对象
    QDir dir(destinationDir);
    // 如果目标目录不存在，则尝试创建它
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "无法创建目标目录:" << destinationDir;
            return false;
        }
    }
    // 生成目标文件路径
    //若目标文件已经存在且md5相同则跳过任务
    QString fileName = QFileInfo(file).fileName();
    QString destinationFilePath = dir.filePath(fileName);
    if (QFile::exists(destinationFilePath))
    {
        if (fileMD5(destinationFilePath) == fileMD5(filePath))
        {
            //不要修改
            return true;
        }
        else {
            //需要删除复制地址的文件
            QFile::remove(destinationFilePath);
        }
    }
    // 复制文件
    if (QFile::copy(filePath, destinationFilePath)) {
        qDebug() << "文件已成功复制到:" << destinationFilePath;
        return true;
    } else {
        qDebug() << "文件复制失败:" << file.errorString();
        return false;
    }
}
