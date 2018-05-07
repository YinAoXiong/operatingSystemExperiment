#ifndef RAMWIDGET_H
#define RAMWIDGET_H
typedef unsigned long long ull;

#include <QWidget>
#include <QPainter>
#include <map>
#include "data.h"
//用于绘制内存详情的QWidget类

using namespace std;

class RAMWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RAMWidget(QWidget *parent = nullptr);
    //1kb占用的宽带，单位px
    int showSize=1;
    //绘图开始的地方
    ull beginRAM;
    //绘图大小
    ull ramsize;
    void setuseRAM(map<long long,colorBlock> * useRAM);
signals:

public slots:
protected:
    //重写该函数进行绘制
    void paintEvent(QPaintEvent *);
private:
    map<long long,colorBlock> * useRAM;

};

#endif // RAMWIDGET_H
