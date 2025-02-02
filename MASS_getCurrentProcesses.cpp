#include "mainwindow.h"
#include "ui_mainwindow.h"

QStringList MASSForm::getCurrentProcesses()
{
    // 使用tasklist命令获取进程列表
    QProcess process;
    process.start("tasklist", QIODevice::ReadOnly);
    process.waitForFinished(); // 等待命令执行完成

    QString output = process.readAllStandardOutput(); // 获取标准输出
    QStringList lines = output.split("\r\n"); // 将输出分行

    return lines;
}
