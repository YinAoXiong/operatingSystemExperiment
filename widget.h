#ifndef WIDGET_H
#define WIDGET_H

#include <algorithm>
#include <vector>
#include <map>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QScrollArea>
#include "jcb.h"
#include "qpushbuttonreserve.h"
#include "pcb.h"
#include "qpushbuttonready.h"
#include "schedulingalgorithm.h"
#include "ramwidget.h"
#include "data.h"
using namespace std;

extern int systemTime;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //根据选择的算法对后备队列进行重新排序
    void sortReserveQueue();
    //根据选择的算法对就绪队列进行重新排序
    void sortReadyQueue();

private slots:
    //添加作业按钮的槽函数
    void on_pushButtonPushJob_clicked();
    //开机按钮的槽函数
    void on_pushButtonTurnOn_clicked();
    //接收定时器信号的系统时间槽函数
    void receiveTimer();
    //关机按钮的槽函数
    void on_pushButtonTurnOff_clicked();
    //用于处理挂起信号的槽函数
    void doHang(QPushButtonReady *);
    //用于处理解除挂起的槽函数
    void RHang(QPushButtonReady *);

private:
    Ui::Widget *ui;
    //后备队列所在布局
    QVBoxLayout * reserveQVBoxLayout;
    //就绪队列所在布局
    QVBoxLayout * readyQVBoxLayout;
    //挂起队列所在布局
    QVBoxLayout * hangQVBoxLayout;
    //作业队列
    vector<QPushButtonReserve *> reserveQueue;
    //就绪队列
    vector<QPushButtonReady *> readyQueue;
    //挂起队列
    vector<QPushButtonReady *> hangQueue;
    //系统定时器
    QTimer * systemTimer;
    //运行时钟启用标志
    bool openRunTimeClock=false;
    //内存显示滚动区域
    QScrollArea * ramScrollArea;
    //承载RAM显示的QWidget
    RAMWidget * ramWidget;
    //储存剩余内存分区状况map,其中key为RAM起始地址，value为RAM分区大小
    map<long long,ull> * emptyRAM;
    //内存绘制情况map,包括起始位置以及显示的颜色
    map<long long,colorBlock> * useRAM;
    //用于判断内存是否足够,如果足够返回内存起始地址，不足返回-1
    long long RAMIsEnough(QueueButton * );
    //一个进程运行结束后执行的函数
    void processOver();
    //作业调度进程
    void jobSchedulProcess();
    //进程调度进程
    void processSchedulProcess();
    //用于向就绪队列中添加进程,index表示为内存起始位置
    void addProcess(QPushButtonReady * ,long long );
    //用于从就绪队列中删除进程
    void removeProcess();
    //用于处理内存的释放
    void freeRAM(QPushButtonReady *);
};

#endif // WIDGET_H
