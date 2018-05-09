#include "qpushbuttonready.h"

QPushButtonReady::QPushButtonReady(PCB * pcb)
{
    this->pcb=pcb;
    connect(this,&QPushButtonReady::clicked,this,&QPushButtonReady::showDetails);
    this->setText(tr("%1,PID:%2\n点击查看详情").arg(pcb->getName()).arg(pcb->getId()));
}

QPushButtonReady::~QPushButtonReady()
{
    delete pcb;
}

void QPushButtonReady::showDetails()
{
    if(pcb->status==0)
    {
        QString str=tr("PID: %1\n进程名称: %2\n进程优先级: %3\n所需内存大小: %4\n剩余运行时间: %5\n主存起始位置: %6").arg(pcb->getId()).arg(pcb->getName()).arg(pcb->getPriority()).arg(pcb->getNeedRAM()).arg(pcb->getNeedTime()).arg(pcb->getTheBeginOfRAM());
        QMessageBox::information(NULL, tr("Show details"),str);
    }else if(pcb->status==1)
    {
        QString str=tr("PID: %1\n进程名称: %2\n进程优先级: %3\n所需内存大小: %4\n剩余运行时间: %5\n主存起始位置: %6\n是否挂起进程？").arg(pcb->getId()).arg(pcb->getName()).arg(pcb->getPriority()).arg(pcb->getNeedRAM()).arg(pcb->getNeedTime()).arg(pcb->getTheBeginOfRAM());
        QMessageBox::StandardButton response=QMessageBox::information(NULL, tr("挂起"),str, QMessageBox::No|QMessageBox::Yes);
        if(response==QMessageBox::Yes)
        {
            //如果是发出挂起信号
            emit doHang(this);
        }
    }else if(pcb->status==2)
    {
        QString str=tr("PID: %1\n进程名称: %2\n进程优先级: %3\n所需内存大小: %4\n剩余运行时间: %5\n主存起始位置: %6\n是否解除挂起？").arg(pcb->getId()).arg(pcb->getName()).arg(pcb->getPriority()).arg(pcb->getNeedRAM()).arg(pcb->getNeedTime()).arg(pcb->getTheBeginOfRAM());
        QMessageBox::StandardButton response=QMessageBox::information(NULL, tr("解挂"),str, QMessageBox::No|QMessageBox::Yes);
        if(response==QMessageBox::Yes)
        {
            //如果是发出解除挂起信号
            emit RHang(this);
        }
    }

}

ControlBlock * QPushButtonReady::getControlBlock()const
{
    return pcb;
}
