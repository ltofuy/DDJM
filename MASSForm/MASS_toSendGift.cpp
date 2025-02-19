#include "MASSForm.h"
#include "ui_MASSForm.h"

void MASSForm::toSendGift(QString ddlcDirPath, QString giftName, QString code)
{
    //首先判定ddlcDirPath不能为空
    QDir d(ddlcDirPath);
    if (ddlcDirPath.isEmpty() || !d.exists() || ddlcDirPath == ".")
    {
        QMessageBox::warning(NULL, "Wrong Target Folder Path", "Target folder path for DDLC is not correct!", QMessageBox::Ok);
        return;
    }

    //构造正确的characters路径
    QDir dir(ddlcDirPath+"/characters");
    if (!dir.exists())
    {
        //qDebug()<<dir.path();
        dir.mkdir(dir.path());
    }
    if (!dir.exists())
    {
        QMessageBox::warning(NULL, "Wrong Target Folder Path", "Target folder path for DDLC is not correct!", QMessageBox::Ok);
        return;
    }

    //确认赠送
    QSettings qSet(giftStatusConfig, QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    int count=qSet.value("Count/"+code).toInt();

    QString content;
    content = "Are sure to send the gift "+giftName+ " ("+code+")"+" to dear Monika?"+"\n";
    content += "You have already sended: "+QString::number(count)+".";
    QMessageBox::StandardButton a = QMessageBox::information(NULL, "", content, QMessageBox::Yes|QMessageBox::No);
    if (a == QMessageBox::Yes)
    {
        QFile f(dir.path()+"/"+code+".gift");
        if (f.open(QIODevice::Text|QIODevice::WriteOnly))
        {
            f.write("To my dear Monika");
            f.close();
        }

        if (f.exists())
        {
            QMessageBox::information(NULL, "", "Gift sended successful");
            qSet.setValue("Count/"+code, count+1);

            for (int i=0;i<allTypes.count();++i)
            {
                refreshGiftStatus(i);
            }
        }
        else {
            QMessageBox::information(NULL, "", "Gift sended failed, please check the operation privileges");
        }
    }
}
