#include "MASSForm.h"
#include "ui_MASSForm.h"


QFileInfoList MASSForm::getAllFiles(QString directoryPath) {
    QFileInfoList fileInfoList;
    // 创建一个 QDir 对象
    QDir dir(directoryPath);

    // 检查目录是否存在
    if (!dir.exists()) {
        return fileInfoList; // 目录不存在，返回空列表
    }
    // 获取所有的文件和子目录，包括递归
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    QFileInfoList entries = dir.entryInfoList();
    for (const QFileInfo &entry : entries) {
        fileInfoList.append(entry);
        // 如果是目录，则递归调用
        if (entry.isDir()) {
            fileInfoList.append(getAllFiles(entry.filePath()));
        }
    }
    return fileInfoList;
}

QFileInfoList MASSForm::getGiftFiles(QString directoryPath) {
    QFileInfoList fileInfoList;
    QDir dir(directoryPath);
    if (!dir.exists()) {
        return fileInfoList; // 返回空列表如果目录不存在
    }
    // 查找所有后缀为.gift的文件，递归搜索子目录
    fileInfoList = dir.entryInfoList(QStringList() << "*.gift", QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    // 获取子目录
    QFileInfoList subDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &subDirInfo : subDirs) {
        QFileInfoList subFiles = getGiftFiles(subDirInfo.absoluteFilePath());
        fileInfoList.append(subFiles); // 递归得到的文件添加到列表中
    }

    return fileInfoList;
}

QFileInfoList MASSForm::getGiftJsonFiles(QString directoryPath) {
    QFileInfoList fileInfoList;

    QDir dir(directoryPath);
    if (!dir.exists()) {
        return fileInfoList; // 返回空列表如果目录不存在
    }
    // 查找所有后缀为.gift的文件，递归搜索子目录
    fileInfoList = dir.entryInfoList(QStringList() << "*.json", QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    //qDebug()<<"json info:"<<fileInfoList;
    // 获取子目录
    QFileInfoList subDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &subDirInfo : subDirs) {
        QFileInfoList subFiles = getGiftJsonFiles(subDirInfo.absoluteFilePath());
        fileInfoList.append(subFiles); // 递归得到的文件添加到列表中
    }

    return fileInfoList;
}
