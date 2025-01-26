#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::showMASSupport(bool b)
{

    int fade=500;

    //新建控件的渐变效果
    QGraphicsOpacityEffect *mas_oe=new QGraphicsOpacityEffect(ui->widget_mas);
    ui->widget_mas->setGraphicsEffect(mas_oe);

    QPropertyAnimation QPA_fade_in(mas_oe,"opacity", this);
    QPA_fade_in.setDuration(fade);

    float v_start, v_end;
    if (b==true)
    {
        v_start = 0.0;
        v_end = 1.0;
    }
    else {
        v_start = 1.0;
        v_end = 0.0;
    }

    QPA_fade_in.setStartValue(v_start);
    QPA_fade_in.setEndValue(v_end);

    //QPA_fade_in.setEasingCurve(QEasingCurve::InCubic);

    QEventLoop l;
    connect(&QPA_fade_in,SIGNAL(finished()),&l,SLOT(quit()));

    //qDebug()<<"准备执行";
    QPA_fade_in.start();

    if (b == true)
    {
        ui->widget_mas->show();
    }

    l.exec();

    if (b == false)
    {
        ui->widget_mas->hide();
    }

    //qDebug()<<"执行完成";
}
