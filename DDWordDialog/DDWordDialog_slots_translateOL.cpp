#include "DDWordDialog.h"
#include "ui_DDWordDialog.h"

void DDWordDialog::translateOL(QString text)
{
    QString code="https://cn.bing.com/translator?ref=TThis&text="+text.remove(" ")+"&from=en&to=zh-Hans";
    QDesktopServices::openUrl(QUrl(code));
}
