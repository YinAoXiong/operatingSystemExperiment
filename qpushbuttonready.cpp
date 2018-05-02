#include "qpushbuttonready.h"

QPushButtonReady::QPushButtonReady(PCB * pcb)
{
    this->pcb=pcb;
    connect(this,QPushButtonReady::clicked,this,QPushButtonReady::showDetails);
    this->setText(tr("%1\n点击查看详情").arg(pcb->name));
}
QPushButtonReady::~QPushButtonReady()
{
    delete pcb;
}
void QPushButtonReady::showDetails()
{
    QString str=tr("PID: %1\n进程名称: %2\n进程优先级: %3\n所需内存大小: %4\n剩余运行时间: %5\n主存起始位置: %6").arg(pcb->pId).arg(pcb->name).arg(pcb->priority).arg(pcb->needRAM).arg(pcb->untillNeedTime).arg(pcb->theBeginOfRAM);
    QMessageBox::information(NULL, tr("Show details"),str);
}
