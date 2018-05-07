#ifndef QUEUEBUTTON_H
#define QUEUEBUTTON_H
#include <QPushButton>
#include "controlblock.h"
//定义了各种button队列的虚基类

class QueueButton:public QPushButton
{

public:
    QueueButton() {}
    virtual ~QueueButton(){}
    //获取控制块的虚函数
    virtual ControlBlock * getControlBlock()const=0;
public slots:
    //显示详情的虚函数
    virtual void showDetails()=0;
};

#endif // QUEUEBUTTON_H
