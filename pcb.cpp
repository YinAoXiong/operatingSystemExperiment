#include "pcb.h"

PCB::PCB(QString name,unsigned int priority, ull needRAM,ull untillNeedTime,ull theBeginOfRAM)
{
    ++PID;
    this->pId=PID;
    this->name=name;
    this->priority=priority;
    this->needRAM=needRAM;
    this->untillNeedTime=untillNeedTime;
    this->theBeginOfRAM=theBeginOfRAM;
}
