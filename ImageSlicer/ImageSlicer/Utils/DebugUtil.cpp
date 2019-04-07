#include "DebugUtil.h"
#include <QObject>
#include <QPainter>
#include <QResizeEvent>
DebugUtil::CDrawNode::CDrawNode(QWidget *parent) : QWidget(parent)
{
    if (parent)
    {
         parent->installEventFilter(this);
    }
}
DebugUtil::CDrawNode::~CDrawNode()
{

}

void DebugUtil::CDrawNode::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));//设置画笔形式

    QRect rt(this->geometry());

    painter.drawRect(rt);
}

bool DebugUtil::CDrawNode::eventFilter(QObject *target, QEvent *event)
{
    if(target == parent())
    {
        if( event->type() == QEvent::Resize )
        {
            QResizeEvent *resizeEvent = static_cast<QResizeEvent *>(event);
            this->setGeometry(QRect(QPoint(0,0),resizeEvent->size()));
        }
    }
    return QWidget::eventFilter(target,event);
}

void DebugUtil::drawWidget(QWidget *widget)
{
#ifdef QT_NO_DEBUG

#else
    CDrawNode *node = new CDrawNode(widget);
    node->setGeometry(QRect(QPoint(0,0),widget->size()));
    node->show();
#endif
}


DebugUtil::DebugUtil()
{

}
