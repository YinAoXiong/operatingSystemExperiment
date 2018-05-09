#ifndef QPUSHBUTTONRESERVE_H
#define QPUSHBUTTONRESERVE_H
#include <QMessageBox>
#include "queuebutton.h"
#include "jcb.h"
//后备队列的QpushButton类


class QPushButtonReserve:public QueueButton
{
public:
    QPushButtonReserve(JCB * jcb);
    ~QPushButtonReserve();
    ControlBlock * getControlBlock()const override;
public slots:
    //详情展示槽函数
    void showDetails() override;
private:
    JCB * jcb;
};

#endif // QPUSHBUTTONRESERVE_H
