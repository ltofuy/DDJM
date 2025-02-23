#ifndef M2GOFORM_H
#define M2GOFORM_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTimer>
#include <QShowEvent>
#include <QCloseEvent>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class M2GoForm;
}

class M2GoForm : public QWidget
{
    Q_OBJECT

public:
    explicit M2GoForm(QWidget *parent = nullptr);
    ~M2GoForm();

    QTimer *inputTimer;

    //设置已经显示的话语
    QString currentText;

    //当前的全文
    QString fullText;

    //Monika是否在家
    bool isMonikaHome;

    //最后记录的Monika状态 0-未知状态(未设置), 1-正常状态(准备执行旅游), 2-决定去旅游, 3-在旅游中
    int Monika_status;

    //获取指定文件的md5
    QString getMD5(QString filepath);

private:
    Ui::M2GoForm *ui;

protected:
    void showEvent(QShowEvent *e);

    void closeEvent(QCloseEvent *e);

    void changeEvent(QEvent *e);

public slots:
    void updateText();

    //treat
    void treat();

    //从家里到capsule
    void boardCapsule(QString monikaAgent, QString capsuleFolder);

    //回家
    void goBackHome(QString monikaAgentOut);


};

#endif // M2GOFORM_H
