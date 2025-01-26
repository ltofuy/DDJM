#ifndef DDLCWORDDIC_H
#define DDLCWORDDIC_H

#include <QString>
#include <QFile>
#include <QPair>
#include <QVector>

#include <QDebug>

class DDLCWordDic{
private:
    //读取csv到对应人物名, 人物名若包含-1,-2则表示第几周目的情况
    void load(QString path, QString cname);

    //人物内容库;
    QVector<QPair<QString, QStringList>> wordsDictionary;
    /*
    QPair<QString, QStringList> words_Monika;
    QPair<QString, QStringList> words_Sayori_1;
    QPair<QString, QStringList> words_Yuri_1;
    QPair<QString, QStringList> words_Yuri_2;
    QPair<QString, QStringList> words_Natsuki_1;
    QPair<QString, QStringList> words_Natsuki_2;
    */

public:
    //初始化, 直接载入默认的字典库
    DDLCWordDic();
    ~DDLCWordDic();

    //列出某个角色的所有字库, act参数可选, 若参数不对只返还Monika
    QStringList getWords(QString cname, int act);
    QStringList getWords(QString cname);
};


#endif // DDLCWORDDIC_H
