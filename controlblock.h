#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H
#include <QString>

typedef unsigned long long ull;

//控制块子类的抽象基类
class ControlBlock
{
public:
    ControlBlock() {}
    virtual ~ControlBlock(){}
    virtual ull getId()const=0;
    virtual QString getName()const=0;
    virtual unsigned int getPriority()const=0;
    virtual ull getNeedRAM()const=0;
    virtual ull getNeedTime()const=0;
    virtual ull getBeginTime()const=0;
    virtual void setNeedTime(ull untillNeedTime)=0;
};

#endif // CONTROLBLOCK_H
