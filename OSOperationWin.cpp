#include "OSOperationWin.h"

OSOperationWin::OSOperationWin()
{

}

QString OSOperationWin::getCurrentWindowsUsername() {
    QProcess process;
    process.start("cmd.exe", QStringList() << "/c" << "echo %USERNAME%");
    process.waitForFinished(); // 等待命令执行完成
    QString username = process.readAllStandardOutput().trimmed();
    return username;
}

QString OSOperationWin::getCurrentWindowsLocalUsername()
{
    // 获取用户主目录
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    // 从主目录路径中提取用户名
    QString userName = QDir(homeDir).dirName();

    return userName;
}

QString OSOperationWin::currentRoamingPath(QString subDirName)
{
    QString path="C:/Users/"+getCurrentWindowsLocalUsername()+"/AppData/Roaming/"+subDirName;
    return path.replace("/", "\\");
}
