#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("操作系统演示"));
    setWindowIcon(QIcon(QStringLiteral(":/icon.png")));
    //未开机时设置关机按钮不可用
    ui->pushButtonTurnOff->setEnabled(false);
    //为队列所在的scorll area 添加 widget和layout
    QWidget * reserveQWidget=new QWidget;
    reserveQVBoxLayout=new QVBoxLayout;
    reserveQWidget->setLayout(reserveQVBoxLayout);
    ui->ScrollAReareserve->setWidget(reserveQWidget);
    QWidget * readyQWidget=new QWidget;
    readyQVBoxLayout=new QVBoxLayout;
    readyQWidget->setLayout(readyQVBoxLayout);
    ui->scrollAreaReady->setWidget(readyQWidget);
    QWidget * hangQWidget=new QWidget;
    hangQVBoxLayout=new QVBoxLayout;
    hangQWidget->setLayout(hangQVBoxLayout);
    ui->scrollAreaHang->setWidget(hangQWidget);

    //创建内存所在scroll Area,并设定位置和大小
    ramScrollArea=new QScrollArea(this);
    ramScrollArea->setGeometry(1149,80,161,321);
    //创建定时器对象，并进行绑定，暂不启动定时器
    systemTimer=new QTimer(this);
    //设置定时器循环触发
    systemTimer->setSingleShot(false);
    //触发时间间隔为1s
    systemTimer->setInterval(1000);
    connect(systemTimer,&QTimer::timeout,this,&Widget::receiveTimer);
    //默认不启用建筑作业按钮，开机后启用
    ui->pushButtonPushJob->setEnabled(false);


//    JCB * jcb=new JCB("test",1,100,100);
//    QPushButtonReserve * reservedButton=new QPushButtonReserve(jcb);
//    ui->ScrollAReareserve->setWidget(reservedButton);
//    PCB * pcb=new PCB("test",1,100,100,0);
//    QPushButtonReady * readyButton=new QPushButtonReady(pcb);
//    ui->scrollAreaReady->setWidget(readyButton);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonPushJob_clicked()
{
   QString name= ui->lineEditJobName->text();
   unsigned int priority= ui->comboBoxPriority->currentText().toUInt();
   ull needRAM =ui->lineEditRAM->text().toULongLong();
   ull needTime=ui->lineEditTime->text().toULongLong();
   JCB * jcb=new JCB(name,priority,needRAM,needTime,systemTime);
   QPushButtonReserve * reserveButton=new QPushButtonReserve(jcb);
   reserveQueue.push_back(reserveButton);
   //对后备队列进行排序
   sortReserveQueue();

   //清除后备队列中的button
   while(reserveQVBoxLayout->count())
   {
       QWidget * tempWidget=reserveQVBoxLayout->itemAt(0)->widget();
       tempWidget->setParent(NULL);
       reserveQVBoxLayout->removeWidget(tempWidget);
   }
   //将重新排序好的button添加进去
   for(auto item:reserveQueue)
   {
       reserveQVBoxLayout->addWidget(item);
   }

   //调用作业调度处理程序
   jobSchedulProcess();

}

void Widget::on_pushButtonTurnOn_clicked()
{
    systemTimer->start();
    //启用添加作业按钮
    ui->pushButtonPushJob->setEnabled(true);
    //一旦开机后开机按钮无法使用，同时启用关机按钮
    ui->pushButtonTurnOn->setEnabled(false);
    ui->pushButtonTurnOff->setEnabled(true);
    //同时设置选项不可改变
    ui->comboBoxJSA->setEnabled(false);
    ui->comboBoxPSA->setEnabled(false);
    ui->lineEditAllRAM->setEnabled(false);
    //初始化剩余内存大小
    restRAM=ui->lineEditAllRAM->text().toULongLong();
    //初始化内存描述map
    ull RAMsize=ui->lineEditAllRAM->text().toULongLong();
    emptyRAM=new map<long long,ull>();
    emptyRAM->insert(make_pair(0,RAMsize));
    //初始化内存绘制map
    useRAM=new map<long long,colorBlock>();
    //初始化内存显示QWidget
    ramWidget=new RAMWidget;
    ramWidget->setuseRAM(useRAM);
    //此处默认showsize 为1，即1kb内存显示为1个像素，可以通过改变ramWidget->showSize，自行设置
    ramWidget->resize(160,ramWidget->showSize*RAMsize);
    //将其添加到scroll area
    ramScrollArea->setWidget(ramWidget);
}

void Widget::receiveTimer()
{
    //系统时间加一
    ++systemTime;
    //更新显示时间
    ui->lcdNumberSystem->display(systemTime);
    //如果运行时钟开启
    if(openRunTimeClock)
    {
        QPushButtonReady * tempPoint=readyQueue[0];
        PCB * tempPCB=(PCB *)tempPoint->getControlBlock();
        ull tempTime=tempPCB->getNeedTime();
        --tempTime;
        tempPCB->setNeedTime(tempTime);
        //如果为动态优先权则每过一个时间片，降低其优先级一次
        if(ui->comboBoxPSA->currentText()==tr("DP"))
            tempPCB->setPriority(tempPCB->getPriority()+1);
        ui->lcdNumber->display((int)tempTime);
        //tempTime为0表示 进程运行结束
        if(tempTime==0)
        {
            processOver();
        }
    }

    //时间片轮转，此处时间片周期为1s故每秒调用一次进程调度算法
    if(!readyQueue.empty())
        processSchedulProcess();

}

void Widget::on_pushButtonTurnOff_clicked()
{
    //查看系统中是否存在尚未处理的工作
    if(!(readyQueue.empty()&&reserveQueue.empty()&&hangQueue.empty()))
    {
        QString str=tr("系统中仍有任务尚未处理是否强制关机");
        QMessageBox::StandardButton response=QMessageBox::warning(NULL,tr("警告"),str,QMessageBox::No|QMessageBox::Yes);
        if(response==QMessageBox::No)
        {
            return;
        }
    }
    //释放资源

    while (!readyQueue.empty()) {
        removeProcess();
    }
    if(!hangQueue.empty())
    {
        for(auto item:hangQueue)
            delete item;
        hangQueue.clear();
    }
    if(!reserveQueue.empty())
    {
        for(auto item:reserveQueue)
            delete item;
        reserveQueue.clear();
    }
    //重置jcb，pcb静态变量
    JCB::JID=0;
    PCB::PID=0;
    //重置运行标志
    openRunTimeClock=false;

    //停掉系统时钟,并重置系统时间
    systemTimer->stop();
    systemTime=0;
    //调整时钟显示
    ui->lcdNumberSystem->display(88888);
    ui->lcdNumber->display(888);

    //停用添加作业按钮
    ui->pushButtonPushJob->setEnabled(false);
    //一旦关机后关机按钮无法使用，同时启用开机按钮
    ui->pushButtonTurnOff->setEnabled(false);
    ui->pushButtonTurnOn->setEnabled(true);
    //同时设置选项可改变
    ui->comboBoxJSA->setEnabled(true);
    ui->comboBoxPSA->setEnabled(true);
    ui->lineEditAllRAM->setEnabled(true);
}

void Widget::sortReserveQueue()
{
    if(ui->comboBoxJSA->currentText()==tr("SJF"))
    {
        sort(reserveQueue.begin(),reserveQueue.end(),SJF());
    }else if(ui->comboBoxJSA->currentText()==tr("PSA"))
    {
        sort(reserveQueue.begin(),reserveQueue.end(),PSA());
    }else if(ui->comboBoxJSA->currentText()==tr("HRRN"))
    {
        sort(reserveQueue.begin(),reserveQueue.end(),HRRN());
    }
    //先来先服务无需特殊处理
}

void Widget::sortReadyQueue()
{
    if(ui->comboBoxPSA->currentText()==tr("SJF"))
    {
        sort(readyQueue.begin(),readyQueue.end(),SJF());
    }else if(ui->comboBoxPSA->currentText()==tr("PSA")||ui->comboBoxPSA->currentText()==tr("DP"))  //静态优先权和动态优先权算法在排序上是相同的。
    {
        sort(readyQueue.begin(),readyQueue.end(),PSA());
    }else if(ui->comboBoxPSA->currentText()==tr("HRRN"))
    {
        sort(readyQueue.begin(),readyQueue.end(),HRRN());
    }
    //先来先服务无需特殊处理
}

void Widget::processOver()
{
    //关闭进程运行时钟
    openRunTimeClock=false;
    //从就绪队列中删除进程
    removeProcess();
    //调用作业调度程序
    if(!reserveQueue.empty())
        jobSchedulProcess();
}

void Widget::jobSchedulProcess()
{
    //TODO 添加动画代码

    //取后备队列中优先级最高的作业

    QPushButtonReserve * bestJob=reserveQueue[0];

    long long key=RAMIsEnough(bestJob);
    //判断内存是否有空闲空间
    if(key>=0)
    {
        //将其从后备队列中删除
        QWidget * tempWidget=reserveQVBoxLayout->itemAt(0)->widget();
        tempWidget->setParent(NULL);
        reserveQVBoxLayout->removeWidget(tempWidget);
        reserveQueue.erase(reserveQueue.begin());
        ControlBlock * bestJCB=bestJob->getControlBlock();
        //创建pcb并加入就绪队列
        PCB * pcb=new PCB(bestJCB->getName(),bestJCB->getPriority(),bestJCB->getNeedRAM(),bestJCB->getNeedTime(),key,systemTime);
        QPushButtonReady * readyButton=new QPushButtonReady(pcb);
        //连接好信号和槽函数
        connect(readyButton,&QPushButtonReady::doHang,this,&Widget::doHang);

        connect(readyButton,&QPushButtonReady::RHang,this,&Widget::RHang);
        //添加到就绪队列
        addProcess(readyButton,key);
        //删除后备队列button对象
        delete bestJob;
    }
}

long long Widget::RAMIsEnough(QueueButton *button)
{
    ull needRAM=button->getControlBlock()->getNeedRAM();
    for(auto &item:*(emptyRAM))
    {
        if(item.second>=needRAM)
        {
            return item.first;
        }

    }
    if(needRAM<=restRAM)
    {
        map<long long,colorBlock> * newUseRAM=new map<long long,colorBlock>();
        long long index=0;
        for(auto &item:*(useRAM))
        {
            newUseRAM->insert(make_pair(index,colorBlock(item.second.RAMsize,item.second.color)));
            index+=item.second.RAMsize;
        }
        delete useRAM;
        useRAM=newUseRAM;
        ramWidget->setuseRAM(useRAM);
        ramWidget->update();
        map<long long,ull> * newEmptyBlock=new map<long long,ull>();
        ull allRAM=ui->lineEditAllRAM->text().toULongLong();
        newEmptyBlock->insert(make_pair(allRAM-restRAM,restRAM));
        delete emptyRAM;
        emptyRAM=newEmptyBlock;
        return allRAM-restRAM;
    }
    return -1;
}

void Widget::addProcess(QPushButtonReady *readyButton,long long index)
{
    //获取空闲块的大小
    ull emptyBlockSize=(*emptyRAM)[index];
    //实际需要大小的大小
    ull realyNeed = readyButton->getControlBlock()->getNeedRAM();
    //更新剩余内存大小
    restRAM-=realyNeed;
    ramWidget->beginRAM=index;
    ramWidget->ramsize=realyNeed;
    emptyRAM->erase(index);

    if(emptyBlockSize!=realyNeed)
    {
        long long nextBegin=index+realyNeed;
        ull nextSize=emptyBlockSize-realyNeed;
        emptyRAM->insert(make_pair(nextBegin,nextSize));
    }
    //添加颜色块
    useRAM->insert(make_pair(index,colorBlock(realyNeed,QColor(rand()%256, rand()%256, rand()%256, 125))));

    //进行更新绘图
    ramWidget->update();

    readyQueue.push_back(readyButton);
    //对就绪队列进行重新排序
    sortReadyQueue();
    //清除就绪队列中的button
    while (readyQVBoxLayout->count()) {
        QWidget * tempWidget=readyQVBoxLayout->itemAt(0)->widget();
        tempWidget->setParent(NULL);
        readyQVBoxLayout->removeWidget(tempWidget);
    }
    //将重新排序好的button添加进去
    for(auto item:readyQueue)
    {
        readyQVBoxLayout->addWidget(item);
    }

}

void Widget::removeProcess()
{
    QPushButtonReady * readyButton=readyQueue[0];
    ull RAMSize=readyButton->getControlBlock()->getNeedRAM();
    //更新剩余内存大小
    restRAM+=RAMSize;
    readyQueue.erase(readyQueue.begin());
    //释放内存
    freeRAM(readyButton);
    //删除button 对象
    delete readyButton;
}

void Widget::processSchedulProcess()
{
    sortReadyQueue();
    //查看处理器是否空闲
    if(ui->horizontalLayoutRun->count()==0)
    {
        ui->horizontalLayoutRun->addWidget(readyQueue[0]);
        //启用运行时钟
        openRunTimeClock=true;
    }else
    {
        if((QPushButtonReady *)ui->horizontalLayoutRun->itemAt(0)->widget()!=readyQueue[0])
        {
            breakProcess();
        }
    }
    //将需要运行的程序设置为运行状态
    PCB * tempPCB=(PCB *) readyQueue[0]->getControlBlock();
    tempPCB->status=PCB::run;
}

void Widget::freeRAM(QPushButtonReady * button)
{
    PCB * tempPCB=(PCB *)button->getControlBlock();
    long long beginOfRAM=tempPCB->getTheBeginOfRAM();
    ull needRAM=tempPCB->getNeedRAM();

    //释放内存
    //从内存占用map中删除
    useRAM->erase(beginOfRAM);
    ramWidget->update();
    auto befor=emptyRAM->end();
    auto after=emptyRAM->end();
    for(auto iter=emptyRAM->begin();iter!=emptyRAM->end();++iter)
    {
        if(iter->first==beginOfRAM+needRAM)
        {
            after=iter;
        }else if(iter->first+iter->second==beginOfRAM)
        {
            befor=iter;
        }
        if(after!=emptyRAM->end()&befor!=emptyRAM->end())
            break;
    }
    long long newBegin=beginOfRAM;
    ull newSize=needRAM;
    if(befor!=emptyRAM->end())
    {
        newBegin=befor->first;
        newSize+=befor->second;
        emptyRAM->erase(befor);
        if(after!=emptyRAM->end())
        {
            newSize+=after->second;
            emptyRAM->erase(after);
        }
    }else if(after!=emptyRAM->end()) {
        newSize+=after->second;
        emptyRAM->erase(after);
    }

    //插入合并后的空白块
    emptyRAM->insert(make_pair(newBegin,newSize));
}


void Widget::doHang(QPushButtonReady * button)
{
    //将其从就绪队列vector中删除
    int index=0;
    int size=readyQueue.size();
    for(int i=0;i<size;++i)
    {
        if(readyQueue[i]==button)
        {
            index=i;
            readyQueue.erase(readyQueue.begin()+i);
        }
    }
    //将其从视图中删除,注意此处需要减一，因为readyQueue[0]已经不再其中显示
    QWidget * tempWidget=readyQVBoxLayout->itemAt(index-1)->widget();
    tempWidget->setParent(NULL);
    readyQVBoxLayout->removeWidget(tempWidget);
    //将其状态设置为挂起状态
    PCB * tempPCB=(PCB *)button->getControlBlock();
    tempPCB->status=PCB::hang;
    //放入挂起队列和挂起视图
    hangQueue.push_back(button);
    hangQVBoxLayout->addWidget(button);
    //释放原有内存
    freeRAM(button);
}

void Widget::RHang(QPushButtonReady * button)
{
    long long index=RAMIsEnough(button);
    if(index<0)
    {
        QString str=tr("内存不足无法解除挂起，请稍后再试");
        QMessageBox::warning(NULL,tr("警告"),str);
    }else
    {
        int key=0;
        int size=hangQueue.size();
        //从挂起队列中删除
        for(int i=0;i<size;++i)
        {
            if(hangQueue[i]==button)
            {
                hangQueue.erase(hangQueue.begin()+i);
                key=i;
                break;
            }
        }
        //从视图中删除
        QWidget * tempWidget= hangQVBoxLayout->itemAt(key)->widget();
        tempWidget->setParent(NULL);
        hangQVBoxLayout->removeWidget(tempWidget);
        //将状态设置为就绪
        PCB * tempPCB=(PCB *)button->getControlBlock();
        tempPCB->status=PCB::ready;
        //添加到进程
        addProcess(button,index);
    }

}

void Widget::breakProcess()
{
    QWidget * tempWidget= ui->horizontalLayoutRun->itemAt(0)->widget();
    tempWidget->setParent(NULL);
    QPushButtonReady * button=(QPushButtonReady *)tempWidget;
    PCB * tempPCB=(PCB *)button->getControlBlock();
    tempPCB->status=PCB::ready;
    ui->horizontalLayoutRun->removeWidget(tempWidget);
    ui->horizontalLayoutRun->addWidget(readyQueue[0]);
    tempPCB =(PCB *) readyQueue[0]->getControlBlock();
    tempPCB->status=PCB::run;
    //清除就绪队列中的button
    while (readyQVBoxLayout->count()) {
        QWidget * tempWidget=readyQVBoxLayout->itemAt(0)->widget();
        tempWidget->setParent(NULL);
        readyQVBoxLayout->removeWidget(tempWidget);
    }
    //将剩余的pcb显示
    for(int i=1;i<readyQueue.size();++i)
    {
        readyQVBoxLayout->addWidget(readyQueue[i]);
    }
}
