#ifndef MASSFORM_H
#define MASSFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QSettings>
#include <QButtonGroup>
#include <QPushButton>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QProcess>



#include "M2GoForm.h"

#include "OSOperationWin.h"

namespace Ui {
class MASSForm;
}

class MASSForm : public QWidget
{
    Q_OBJECT

public:
    explicit MASSForm(QWidget *parent = nullptr);
    ~MASSForm();

    //存储礼物代码 0-name, 1-code
    QVector<QStringList> giftCode_clothes;
    QVector<QStringList> giftCode_ribbon;
    QVector<QStringList> giftCode_hairclip;
    QVector<QStringList> giftCode_earring;
    QVector<QStringList> giftCode_choker;
    QVector<QStringList> giftCode_gifts;

    QStringList giftCode_clothes_single;
    QStringList giftCode_ribbon_single;
    QStringList giftCode_hairclip_single;
    QStringList giftCode_earring_single;
    QStringList giftCode_choker_single;
    QStringList giftCode_other_single;

    QVector<QStringList> giftAllInfoList;

    //保存未录入的gift
    QVector<QStringList> giftCode_gifts_unknown;

    //所有文件信息;
    QFileInfoList targetsAllInfoList;

    QFileInfoList giftFileInMods;
    QFileInfoList giftJsonInMods;

    int maxRowCount;

    //所有的tableWidgets
    QVector<QTableWidget*> wList;
    //所有的buttonGroups
    QVector<QButtonGroup*> bgs;
    //所有的Labels
    QVector<QVector<QLabel*>> allLabels;

    //礼物的bg
    QButtonGroup bg_clothes;
    QButtonGroup bg_ribbon;
    QButtonGroup bg_hairclip;
    QButtonGroup bg_earring;
    QButtonGroup bg_choker;
    QButtonGroup bg_gifts;

    QFileInfoList getAllFiles(QString directoryPath);
    QFileInfoList getGiftFiles(QString directoryPath);
    QFileInfoList getGiftJsonFiles(QString directoryPath);

    //指定保存的文件, 读取其并刷新当前的送出情况
    void refreshGiftStatus(QVector<QStringList> giftSettings, QString configpath, QTableWidget *w);

    //指定存储配置文件
    QString giftStatusConfig;

    M2GoForm *M2G;

    //win: 获取当前任务列表, 假设大多数玩家是在win启动的MAS
    QStringList getCurrentProcesses();

    //检查是否当前进程包含DDLC
    bool checkProcess(QString exeName);

    //true存档时不在弹出对话框;
    bool isSilentBackup;

    //依据目录判断类型
    //0->clothes
    //1->ribbon
    //2->hairclip
    //3->earring
    //4->other
    int appearanceType(QDir dir);

    //判断四否为thumb
    //type: cloth, ribbon, hairclip, earring, choker, ""
    //codeO: 原始礼物码
    //code: 被处理的礼物码, 一般是删除了cloth, ribbon等段
    bool isThumb(QString typeName, QFileInfo info, QString codeO, QString code, int fileCount);

    //mod的分类只有
    //("ribbon", "left-hair-clip", "clothes", "earrings", "choker", "left-hair-flower")
    //判断来自这个的分类是否是否与本机分类相符合
    bool isMatched(QString modType, QString theType);

private:
    Ui::MASSForm *ui;

protected:
    void changeEvent(QEvent *e);

public slots:
    void buttonOperation_clothes(int a);
    void buttonOperation_ribbon(int a);
    void buttonOperation_hairclip(int a);
    void buttonOperation_earring(int a);
    void buttonOperation_choker(int a);
    void buttonOperation_gifts(int a);

    //通用的函数, 用于写礼物
    void toSendGift(QString ddlcDirPath, QString giftName, QString code);

    //查找文件夹
    void findDir();

    //refresh monika love
    void refreshMonikaLove();

    //启动DDLC
    void visitMonika();

    //制作存档保存
    void makeBackup();
    //QString makeBackupAndReturnInformation();

    //重置存档
    void reload();
};

#endif // MASSFORM_H
