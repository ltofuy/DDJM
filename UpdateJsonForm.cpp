#include "UpdateJsonForm.h"
#include "ui_UpdateJsonForm.h"

UpdateJsonForm::UpdateJsonForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateJsonForm)
{
    ui->setupUi(this);
}

UpdateJsonForm::~UpdateJsonForm()
{
    delete ui;
}


void UpdateJsonForm::writeTo(QString filepath)
{
    QFile f(filepath);
    if (f.open(QIODevice::Text|QIODevice::WriteOnly))
    {
        f.write(ui->plainTextEdit->toPlainText().toUtf8());
        f.flush();
        f.close();
    }
}
