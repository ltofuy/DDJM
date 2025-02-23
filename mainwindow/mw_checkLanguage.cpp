#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::checkLanguage()
{
    QString zone = QLocale::system().name();

    QSettings qSet(QDir::currentPath()+"/Config/"+QString(APP_NAME)+"_config.ini", QSettings::IniFormat);
    qSet.setIniCodec("utf-8");

    //若settings之中已经设置则使用settings的处理
    if (qSet.allKeys().contains("UI/Language"))
    {
        //则使用设置的语言;
        int language_index = qSet.value("UI/Language").toInt();

        switch (language_index) {
        case 0:
            //English, no need to translate
            zone = "en";
            break;
        case 1:
            //zh_CN translate
            zone = "zh_CN";
            break;
        }

        //依据zone, 在目标目录处理所有的翻译问题;
        QString trDirpath=QDir::currentPath()+"/translations";
        //读取目标目录下的所有文件信息;
        QDir trDir(trDirpath);
        trDir.setFilter(QDir::NoDotAndDotDot);
        QFileInfoList fileList=trDir.entryInfoList(QDir::Files);
        qDebug()<<fileList;
        //载入
        QString languageFileSuffix="qm";
        for (int i=0;i<fileList.count();++i)
        {
            if (fileList.at(i).suffix()==languageFileSuffix)
            {
                QString baseName=fileList.at(i).baseName();
                if (baseName.lastIndexOf(zone)==baseName.count()-zone.count())
                {
                    //那就读取文件;
                    QString filepath=fileList.at(i).canonicalFilePath();
                    //用QTranslater翻译;
                    QTranslator *translator=new QTranslator;
                    translator->load(filepath);
                    qApp->installTranslator(translator);
                }
            }
        }

        //处理完就结束
        qDebug()<<"处理完成checkLanguage";
        return;
    }



    if (zone == "zh_CN")
    {
        //询问用户是否要翻译;

        QString content = "检测到您当前的电脑运行的语言是简体中文，但您未设置"+QString(APP_NAME)+"的语言，因而软件依然默认以英文运行。";
        content += "若您对英文不熟悉，则继续使用本软件会略微困难。";
        content += "\n\n";
        content += "您是否需要翻译（为中文）？";
        content += "\n";
        content += "需要说明，翻译后一些在本软件的对话可能会失去原有英文意味，这可能会降低您陪伴Monika的体验，显得脱戏。";
        content += "\n";
        content += "翻译后就意味着您和Monika在"+QString(APP_NAME)+"的交流总是有一个第三者在做转述，请问您是否执意要翻译？";
        content += "\n";
        content += "该翻译并不会对原游戏的语言产生影响，其仅影响"+QString(APP_NAME)+"的设置。若未来您需要切换回英文，请将程序Config/"+QString(APP_NAME)+"_config.ini的UI/Language项改为0";
        content += "\n\n";
        content += "Yes: 翻译，设置为中文运行";
        content += "\n";
        content += "No或取消: 不翻译，设置为英文运行";

        QMessageBox::StandardButton a= QMessageBox::information(nullptr, "翻译设置(仅需一次)", content, QMessageBox::Yes|QMessageBox::No);
        switch (a) {
        case QMessageBox::Yes:
        {
            zone = "zh_CN";
            qSet.setValue("UI/Language", 1);
        }
            break;
        default:
        {
            zone = "en";
            qSet.setValue("UI/Language", 0);
        }
            break;
        }

        //依据zone, 在目标目录处理所有的翻译问题;
        QString trDirpath=QDir::currentPath()+"/translations";
        //读取目标目录下的所有文件信息;
        QDir trDir(trDirpath);
        trDir.setFilter(QDir::NoDotAndDotDot);
        QFileInfoList fileList=trDir.entryInfoList(QDir::Files);
        //载入
        QString languageFileSuffix="qm";
        for (int i=0;i<fileList.count();++i)
        {
            if (fileList.at(i).suffix()==languageFileSuffix)
            {
                QString baseName=fileList.at(i).baseName();
                if (baseName.lastIndexOf(zone)==baseName.count()-zone.count())
                {
                    //那就读取文件;
                    QString filepath=fileList.at(i).canonicalFilePath();
                    //用QTranslater翻译;
                    QTranslator *translator=new QTranslator;
                    translator->load(filepath);
                    qApp->installTranslator(translator);
                }
            }
        }

        qDebug()<<"处理完成checkLanguage";
    }
}
