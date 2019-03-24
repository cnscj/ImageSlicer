#include "CGridArea.h"
#include <QPainter>

CGridArea::CGridArea(QWidget *parent) : QWidget(parent)
{

}

void CGridArea::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QPen(Qt::blue,4,Qt::DashLine));//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式
//    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,160,160);

}


CGridArea::CGridItem::CGridItem(QWidget *parent) : QWidget(parent)
{

}
