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
    QVector<QStringList> giftCode_gifts;

    //保存未录入的gift
    QVector<QStringList> giftCode_gifts_unknown;

    QFileInfoList giftFileInMods;

    //礼物的bg
    QButtonGroup bg_clothes;
    QButtonGroup bg_ribbon;
    QButtonGroup bg_gifts;

    QFileInfoList getGiftFiles(QString directoryPath);


    //指定保存的文件, 读取其并刷新当前的送出情况
    void refreshGiftStatus(QVector<QStringList> giftSettings, QString configpath, QTableWidget *w);

    //指定存储配置文件
    QString giftStatusConfig;

    M2GoForm *M2G;

private:
    Ui::MASSForm *ui;


public slots:
    void buttonOperation_clothes(int a);
    void buttonOperation_ribbon(int a);
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
};

#endif // MASSFORM_H
