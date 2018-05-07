#include "ramwidget.h"

RAMWidget::RAMWidget(QWidget *parent) : QWidget(parent)
{

}

void RAMWidget::setuseRAM(map<long long, colorBlock> *useRAM)
{
    this->useRAM=useRAM;
}

void RAMWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    painter.setPen(pen); //添加画笔
    for(auto &item:(*useRAM))
    {
        QBrush brush(item.second.color);
        painter.setBrush(brush); //添加画刷
        painter.drawRect(0,item.first,160,showSize*item.second.RAMsize);
    }
}
