#include "CGridArea.h"
#include <QPainter>
#include <QMouseEvent>

CGridArea::CGridArea(QWidget *parent) : QWidget(parent), m_scale(1.0)
{
    //貌似与位置有关
    for (int i = 0; i<1; i++)
    {
        for (int j = 0; j<1; j++)
        {
            CGridItem *a = new CGridItem(this);
            a->setGeometry(QRect(20*i,20*j,20,20));
            m_itesList.push_back(a);
            a->update();
        }
    }
}

void CGridArea::setScale(double scale)
{
    m_scale = scale;
}

double CGridArea::getScale()
{
    return m_scale;
}

void CGridArea::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

}

void CGridArea::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
//    qDebug("%d,%d|%d,%d",event->oldSize().width(),event->oldSize().height(),event->size().width(),event->size().height());
}

/////////////////////
/////////////////////
CGridArea::CGridItem::CGridItem(QWidget *parent) : QWidget(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(mouseClicked()));
}


void CGridArea::CGridItem::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式
//    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
    QRect rt(QRect(0,0,this->size().width(),this->height()));//TODO:随主窗口缩放
    painter.drawRect(rt);

}

void CGridArea::CGridItem::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

}

void CGridArea::CGridItem::mouseClicked()
{
    //处理代码
    qDebug("%d_%d_%d_%d",this->geometry().x(),this->geometry().y(),this->geometry().width(),this->geometry().height());
}

void CGridArea::CGridItem::mousePressEvent(QMouseEvent *e)
{
    m_mouserPos = QPoint(e->x(), e->y());
}

void CGridArea::CGridItem::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_mouserPos == QPoint(e->x(), e->y()))
    {
        emit clicked();
    }
}

