#include "qpushbuttonreserve.h"

QPushButtonReserve::QPushButtonReserve(JCB * jcb)
{
    this->jcb=jcb;
    connect(this,&QPushButtonReserve::clicked,this,&QPushButtonReserve::showDetails);
    this->setText(tr("%1,JID:%2\n点击查看详情").arg(jcb->getName()).arg(jcb->getId()));
}

QPushButtonReserve::~QPushButtonReserve()
{
    delete jcb;
}

void QPushButtonReserve::showDetails()
{
    QString str=tr("JID: %1\n作业名称: %2\n作业优先级: %3\n所需内存大小: %4\n运行所需时间%5").arg(jcb->getId()).arg(jcb->getName()).arg(jcb->getPriority()).arg(jcb->getNeedRAM()).arg(jcb->getNeedTime());
    QMessageBox::information(NULL, tr("Show details"),str);
}

ControlBlock * QPushButtonReserve::getControlBlock()const
{
    return jcb;
}
