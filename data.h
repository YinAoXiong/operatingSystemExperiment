#ifndef DATA_H
#define DATA_H
typedef unsigned long long ull;
#include <QColor>
struct colorBlock
{
    ull RAMsize;
    QColor color;
    colorBlock(ull RAMsize,QColor color) {
        this->RAMsize=RAMsize;
        this->color=color;
    }
};

#endif // DATA_H
