#ifndef JCB_H
#define JCB_H
#include <QString>
//JCB 类用于处理作业控制块

typedef unsigned long long ull;
class JCB
{
public:
    static ull JID;     //静态成员变量作为后备队列 元素的标识符，每创建一个就加1
    ull jId;
    QString name;
    unsigned int priority;
    ull needRAM;        //单位kb
    ull needTime;

    JCB(QString name,unsigned int priority, ull needRAM,ull needTime);
};

#endif // JCB_H
