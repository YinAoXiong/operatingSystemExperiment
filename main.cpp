#include "widget.h"
#include <QApplication>
typedef unsigned long long ull;

//静态成员变量初始化
ull JCB::JID=0;
ull PCB::PID=0;

//系统时间 单位秒 初始化为0
int systemTime=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
