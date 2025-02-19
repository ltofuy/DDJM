#include "MASSForm.h"
#include "ui_MASSForm.h"

QJsonObject MASSForm::loadJson(QString jsonfilepath)
{
    QJsonObject object;
    if (jsonfilepath.toLower().endsWith(".json") == false)
    {
        qDebug()<<"jsonfilepath?: "<<jsonfilepath;
        return object;
    }

    // 打开JSON文件
    QFile file(jsonfilepath);
    if (file.open(QIODevice::ReadOnly)) {
        // 读取文件内容
        QByteArray jsonData = file.readAll();
        file.close();
        // 解析JSON数据
        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
        if (jsonDoc.isNull()) {
            qDebug()<<"A Null Json"<<jsonfilepath;
            return object;
        }
        // 确保JSON文档是一个对象
        if (!jsonDoc.isObject()) {
            return object;
        }
        QJsonObject jsonObj = jsonDoc.object();
        //返还获取的新的jsonObj
        return jsonObj;
    }

    return object;
}
