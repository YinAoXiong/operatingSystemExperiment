#include "jcb.h"

JCB::JCB(QString name,unsigned int priority, ull needRAM,ull needTime,ull beginTime)
{
    ++JID;
    this->jId=JID;
    this->name=name;
    this->priority=priority;
    this->needRAM=needRAM;
    this->needTime=needTime;
    this->beginTime=beginTime;
}

ull JCB::getId()const
{
    return jId;
}

QString JCB::getName()const
{
    return name;
}

unsigned int JCB::getPriority()const
{
    return priority;
}

ull JCB::getNeedRAM()const
{
    return needRAM;
}

ull JCB::getNeedTime()const
{
    return needTime;
}

ull JCB::getBeginTime()const
{
    return beginTime;
}

void JCB::setNeedTime(ull needTime)
{
    this->needTime=needTime;
}
