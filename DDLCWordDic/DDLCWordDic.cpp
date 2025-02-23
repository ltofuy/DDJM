#include "DDLCWordDic.h"

DDLCWordDic::DDLCWordDic()
{
    //顺序为封面从左到右

    //A 0
    load(":/Resource/Sayori-1.csv", "Sayori-1");

    //B 12
    load(":/Resource/Yuri-1.csv", "Yuri-1");
    load(":/Resource/Yuri-2.csv", "Yuri-2");


    //C 34
    load(":/Resource/Natsuki-1.csv", "Natsuki-1");
    load(":/Resource/Natsuki-2.csv", "Natsuki-2");

    //D 5
    load(":/Resource/Monika.csv", "Monika");

}

DDLCWordDic::~DDLCWordDic()
{

}

void DDLCWordDic::load(QString path, QString cname)
{
    QFile f(path);
    QString content="";

    if (f.exists())
    {
        if (f.open(QIODevice::Text|QIODevice::ReadOnly))
        {
            content=QString::fromUtf8(f.readAll());
            f.close();
        }
    }
    else {
        qDebug()<<"Lost: "+path+" for "+cname;
    }

    //对读取的结果进行处理;
    QStringList words=QStringList();
    QStringList lines=content.split("\n");
    for (int i=0;i<lines.count();++i)
    {
        QStringList ls=lines.at(i).split(",");
        for (int j=0;j<ls.count();++j)
        {
            QString part=ls.at(j);
            part=part.remove(" ").toLower();
            if (part!="")
            {
                words<<part;
            }
        }
    }

    //写入角色
    wordsDictionary<<QPair<QString, QStringList>(cname, words);
}

QStringList DDLCWordDic::getWords(QString cname, int act)
{
    if (cname.toLower()=="sayori" || cname.toLower() == "s")
    {
        return wordsDictionary.at(0).second;
    }

    if (cname.toLower()=="yuri" || cname.toLower() == "y")
    {
        //考虑不同周目的情况
        QStringList usedWords=wordsDictionary.at(1).second;
        if (act == 1)
        {

        }
        if (act == 2)
        {
            //还要增加周目1的情况
            usedWords += wordsDictionary.at(2).second;
        }
        return usedWords;
    }

    if (cname.toLower()=="natsuki" || cname.toLower() == "n")
    {
        //考虑不同周目的情况
        QStringList usedWords=wordsDictionary.at(3).second;
        if (act == 1)
        {

        }
        if (act == 2)
        {
            //还要增加周目1的情况
            usedWords += wordsDictionary.at(4).second;
        }
        return usedWords;
    }

    //上述情况都不是, 返还Monika!!! Just Monika!!!
    return wordsDictionary.at(5).second;
}

QStringList DDLCWordDic::getWords(QString cname)
{
    //只指定第一周目
    return getWords(cname, 1);
}
