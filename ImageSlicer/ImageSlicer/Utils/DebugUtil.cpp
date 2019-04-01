#include "DebugUtil.h"
#include <QPainter>

DebugUtil::CDrawNode::CDrawNode(QWidget *parent) : QWidget(parent)
{

}
DebugUtil::CDrawNode::~CDrawNode()
{

}

void DebugUtil::CDrawNode::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));//设置画笔形式
//    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式

    QRect rt(QRect(this->geometry().x(),this->geometry().x(),this->geometry().width() - 1,this->geometry().height() - 1));

    painter.drawRect(rt);
}


void DebugUtil::drawWidget(QWidget *widget)
{
#ifdef QT_NO_DEBUG

#else
    CDrawNode *node = new CDrawNode(widget);
    node->setGeometry(widget->geometry());
    node->show();
#endif
}


DebugUtil::DebugUtil()
{

}
