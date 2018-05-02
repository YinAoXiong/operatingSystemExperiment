#include "jcb.h"

JCB::JCB(QString name,unsigned int priority, ull needRAM,ull needTime)
{
    ++JID;
    this->jId=JID;
    this->name=name;
    this->priority=priority;
    this->needRAM=needRAM;
    this->needTime=needTime;
}
