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
#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPoint>
#include <QSettings>

#include "M2GoForm.h"

#include "OSOperationWin.h"

#include "ez_write_log.h"

namespace Ui {
class MASSForm;
}

class MASSForm : public QWidget
{
    Q_OBJECT

public:
    explicit MASSForm(QWidget *parent = nullptr);
    ~MASSForm();

    //所有文件信息;
    QFileInfoList giftJsonInMods;
    //所有thumb信息
    QFileInfoList thumbFileList;

    //不再需要旧的内容, 直接使用新的进行初始化
    //使用如下的就够了
    //每个QStringList 0:code, 1:group, 2:thumb, 3:display, 4 精确地址
    QVector<QStringList> giftAllInfoList;
    QStringList allTypes;

    //每个分类的最大个数
    int maxRowCount;

    //涉及所有分类的部分
    //所有的tableWidgets
    QVector<QTableWidget*> wList;
    //所有的buttonGroups
    QVector<QButtonGroup*> bgs;
    //所有的Labels
    QVector<QVector<QLabel*>> allLabels;

    QFileInfoList getAllFiles(QString directoryPath);
    QFileInfoList getGiftFiles(QString directoryPath);
    QFileInfoList getGiftJsonFiles(QString directoryPath);

    //单独涉及ui操作的按钮
    QButtonGroup bgUI;

    //指定存储配置文件
    QString giftStatusConfig;

    M2GoForm *M2G;

    //win: 获取当前任务列表, 假设大多数玩家是在win启动的MAS
    QStringList getCurrentProcesses();

    //检查是否当前进程包含DDLC
    bool checkProcess(QString exeName);

    //true存档时不在弹出对话框;
    bool isSilentBackup;

    //用于临时记录备份时的文件夹名
    QString temp_backup_dirname;
    QString temp_backup_dirpath;


    // 【作废】依据目录判断类型
    int appearanceType(QDir dir);

    // 【作废】判断四否为thumb
    //type: cloth, ribbon, hairclip, earring, choker, ""
    //codeO: 原始礼物码
    //code: 被处理的礼物码, 一般是删除了cloth, ribbon等段
    bool isThumb(QString typeName, QFileInfo info, QString codeO, QString code, int fileCount);

    // 【作废】mod的分类只有
    //("ribbon", "left-hair-clip", "clothes", "earrings", "choker", "left-hair-flower")
    //判断来自这个的分类是否是否与本机分类相符合
    bool isMatched(QString modType, QString theType);

    //需要一个读取json的数据结果
    QVector<QJsonObject> jsonObjects;

    //读取json
    QJsonObject loadJson(QString jsonfilepath);

private:
    Ui::MASSForm *ui;

protected:
    void changeEvent(QEvent *e);

public slots:
    void buttonOperationGiftSended(int a);

    void buttonOperation(int a);

    //通用的函数, 用于写礼物
    void toSendGift(QString ddlcDirPath, QString giftName, QString code);

    //查找文件夹
    void findDir();

    //refresh monika love
    void refreshMonikaLove();

    //启动DDLC
    void visitMonika();

    //打开DDLC所在文件夹
    void openDDLCFolder();

    //制作存档保存
    void makeBackup();
    //QString makeBackupAndReturnInformation();

    //重置存档
    void reload();

    //指定保存的文件, 读取其并刷新当前的送出情况
    void refreshGiftStatus(int a);

    //同步功能
    void sync();
};

#endif // MASSFORM_H
