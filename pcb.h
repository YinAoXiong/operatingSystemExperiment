#ifndef PCB_H
#define PCB_H
#include <QString>
#include <controlblock.h>

typedef unsigned long long ull;
//PCB 用于处理进程控制块
class PCB:public ControlBlock
{
public:
    //静态成员变量作为就绪队列 元素的标识符，每创建一个就加1
    static ull PID;
    //statu 常量增加可读性
    const static int run=0;
    const static int ready=1;
    const static int hang=2;
    //程序运行状态,运行为0，就绪为1，挂起为2
    int status=1;
    PCB(QString name,unsigned int priority, ull needRAM,ull untillNeedTime,ull theBeginOfRAM,ull beginTime);
    ull getId()const override;
    QString getName()const override;
    unsigned int getPriority()const override;
    ull getNeedRAM()const override;
    ull getNeedTime()const override;
    ull getBeginTime()const override;
    void setNeedTime(ull untillNeedTime) override;
    ull getTheBeginOfRAM()const;
    void setPriority(unsigned int priority);

private:
    //每个进程拥有的id
    ull pId;
    //进程名
    QString name;
    //进程优先级
    unsigned int priority;
    ull needRAM;
    //剩余需要时间
    ull untillNeedTime;
    //主存起始位置
    ull theBeginOfRAM;
    //开始进入时间
    ull beginTime;
};

#endif // PCB_H
