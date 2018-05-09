#ifndef QPUSHBUTTONREADY_H
#define QPUSHBUTTONREADY_H

#include <QMessageBox>
#include "queuebutton.h"
#include "pcb.h"

class QPushButtonReady:public QueueButton
{
    Q_OBJECT

public:
    QPushButtonReady(PCB * pcb);
    ~QPushButtonReady();
    ControlBlock * getControlBlock()const override;
signals:
    //自定义挂起信号
    void doHang(QPushButtonReady *);
    void RHang(QPushButtonReady *);
public slots:
    //详情展示槽函数
    void showDetails() override;
private:
    PCB * pcb;
};

#endif // QPUSHBUTTONREADY_H
