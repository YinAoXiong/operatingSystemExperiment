#ifndef JCB_H
#define JCB_H
#include <QString>
#include "controlblock.h"

typedef unsigned long long ull;
//JCB 类用于处理作业控制块
class JCB:public ControlBlock
{
public:
    //静态成员变量作为后备队列 元素的标识符，每创建一个就加1
    static ull JID;
    JCB(QString name,unsigned int priority, ull needRAM,ull needTime,ull beginTime);
    ull getId()const override;
    QString getName()const override;
    unsigned int getPriority()const override;
    ull getNeedRAM()const override;
    ull getNeedTime()const override;
    ull getBeginTime()const override;
    void setNeedTime(ull needTime) override;
private:
    //每个jcb拥有的id
    ull jId;
    //作业名
    QString name;
    //优先级
    unsigned int priority;
    //需要的空间大小 单位kb
    ull needRAM;
    //所需时间 单位秒
    ull needTime;
    //进入时间 单位秒
    ull beginTime;
};

#endif // JCB_H
