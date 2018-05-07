#include "pcb.h"

PCB::PCB(QString name,unsigned int priority, ull needRAM,ull untillNeedTime,ull theBeginOfRAM,ull beginTime)
{
    ++PID;
    this->pId=PID;
    this->name=name;
    this->priority=priority;
    this->needRAM=needRAM;
    this->untillNeedTime=untillNeedTime;
    this->theBeginOfRAM=theBeginOfRAM;
    this->beginTime=beginTime;
}

ull PCB::getId()const
{
    return pId;
}

QString PCB::getName()const
{
    return name;
}

unsigned int PCB::getPriority()const
{
    return priority;
}

ull PCB::getNeedRAM()const
{
    return needRAM;
}

ull PCB::getNeedTime()const
{
    return untillNeedTime;
}

ull PCB::getBeginTime()const
{
    return beginTime;
}

ull PCB::getTheBeginOfRAM()const
{
    return theBeginOfRAM;
}

void PCB::setNeedTime(ull untillNeedTime)
{
    this->untillNeedTime=untillNeedTime;
}

void PCB::setPriority(unsigned int priority)
{
    this->priority=priority;
}
