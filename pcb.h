#ifndef PCB_H
#define PCB_H
#include <QString>
//PCB 用于处理进程控制块

typedef unsigned long long ull;

class PCB
{
public:
    static ull PID;       //静态成员变量作为就绪队列 元素的标识符，每创建一个就加1
    ull pId;
    QString name;
    unsigned int priority;
    ull needRAM;
    ull untillNeedTime;
    ull theBeginOfRAM;
    PCB(QString name,unsigned int priority, ull needRAM,ull untillNeedTime,ull theBeginOfRAM);
};

#endif // PCB_H
