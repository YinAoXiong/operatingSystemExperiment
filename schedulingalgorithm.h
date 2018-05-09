#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H
#include "queuebutton.h"

extern int systemTime;

//调度算法的实现

//段作业优先算法实现
struct SJF
{
    bool operator () (QueueButton * source1,QueueButton * source2)
    {
        ControlBlock * cb1=source1->getControlBlock();
        ControlBlock * cb2=source2->getControlBlock();
        return cb1->getNeedTime()<cb2->getNeedTime();
    }
};

//优先级调度算法实现,数值越小优先级越高
struct PSA
{
    bool operator () (QueueButton * source1,QueueButton * source2)
    {
        ControlBlock * cb1=source1->getControlBlock();
        ControlBlock * cb2=source2->getControlBlock();
        return cb1->getPriority()<cb2->getPriority();
    }
};

//高响应比优先级调度算法
struct HRRN
{
    bool operator () (QueueButton * source1,QueueButton * source2)
    {
        ControlBlock * cb1=source1->getControlBlock();
        ControlBlock * cb2=source2->getControlBlock();
        long double priorty1=(systemTime-cb1->getBeginTime())/cb1->getNeedTime()+1;
        long double priorty2=(systemTime-cb2->getBeginTime())/cb1->getNeedTime()+1;
        return priorty1<priorty2;
    }
};


#endif // SCHEDULINGALGORITHM_H
