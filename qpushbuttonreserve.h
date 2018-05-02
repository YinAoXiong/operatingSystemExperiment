#ifndef QPUSHBUTTONRESERVE_H
#define QPUSHBUTTONRESERVE_H
#include <QPushButton>
#include <QMessageBox>
#include "jcb.h"
//后备队列的QpushButton类


class QPushButtonReserve:public QPushButton
{
public:
    QPushButtonReserve(JCB * jcb);
    ~QPushButtonReserve();
public slots:
    void showDetails();
private:
    JCB * jcb;
};

#endif // QPUSHBUTTONRESERVE_H
