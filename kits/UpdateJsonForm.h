#ifndef UPDATEJSONFORM_H
#define UPDATEJSONFORM_H

#include <QWidget>
#include <QFile>

namespace Ui {
class UpdateJsonForm;
}

class UpdateJsonForm : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateJsonForm(QWidget *parent = nullptr);
    ~UpdateJsonForm();

    //写入到文件
    void writeTo(QString filepath);


private:
    Ui::UpdateJsonForm *ui;
};

#endif // UPDATEJSONFORM_H
