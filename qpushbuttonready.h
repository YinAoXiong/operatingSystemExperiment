#ifndef QPUSHBUTTONREADY_H
#define QPUSHBUTTONREADY_H
#include <QPushButton>
#include <QMessageBox>
#include "pcb.h"

class QPushButtonReady:public QPushButton
{
public:
    QPushButtonReady(PCB * pcb);
    ~QPushButtonReady();
public slots:
    void showDetails();
private:
    PCB * pcb;
};

#endif // QPUSHBUTTONREADY_H
