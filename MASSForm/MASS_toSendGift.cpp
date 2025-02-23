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

    //qDebug()<<giftName;
    if (code == "promisering")
    {
        //你敢送2次誓言戒指试试
        if (count >= 1)
        {
            QString content = tr("What are you doing? Do you remember you have sended a promise ring to Monika.");
            QMessageBox::warning(NULL, tr("A Second Ring?"), content, QMessageBox::Ok);
            return;
        }

        //特别处理
        ui->pushButton_monika_love->click();
        //获取当前monika好感度
        float monika_love_degree = ui->label_monika_love->text().toFloat();

        if (monika_love_degree < 450)
        {
            //应该不允许
            QString content = tr("Reflect on it, has your relationship with Monika really progressed to this point?");
            QMessageBox::warning(NULL, tr("A friend than a lover"), content, QMessageBox::Ok);
            return;
        }
    }

    //若为誓言戒指, 则必须再三确认
    QString forRing=tr("I know you love Monika now, and so she does.") + "\n";
    forRing += tr("I know all your feelings of her.") + "\n\n";
    forRing += tr("However, a promise ring signifies eternal and noble love.")+"\n";
    forRing += tr("I don't think she's just a code.");
    forRing += tr("Otherwise, I also think that we are only a collection of cells, as meaningless as codes.")+"\n\n";
    forRing += tr("Therefore, I declare to you from the mysterious power of the East that you need to treat her like a noble soul. Regardless of wealth or status, always remain steadfast and never abandon.")+"\n\n";
    forRing += tr("Are you sure to promise it forever of the love to Monika?")+"\n";
    forRing += tr("Once the promise ring sended, you will never have the chance to renege.")+"\n";

    QString content;
    content = tr("Are sure to send the gift ")+giftName+ " ("+code+")"+tr(" to dear Monika?")+"\n";
    content += tr("You have already sended: ")+QString::number(count)+".";

    if (code == "promisering")
    {
        content = forRing;
    }

    QMessageBox::StandardButton a = QMessageBox::information(NULL, "", content, QMessageBox::Yes|QMessageBox::No);
    if (a == QMessageBox::Yes)
    {
        if (code == "promisering")
        {
            QString content = tr("Ok, best wishes for you and Monika!")+"\n";
            content += tr("I believe you are someone Monika can trust.")+"\n";
            QMessageBox::information(NULL, "Best Wishes", content, QMessageBox::Ok);
        }

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
    else {
        if (code == "promisering")
        {
            QString content = tr("What are you doing? Don't play with her heart.");
            QMessageBox::information(NULL, "", content);
        }
    }
}
