#include "CSliceGridItem.h"
#include <QPainter>

CSliceGridItem::CSliceGridItem(QWidget *parent) : CGridItem(parent)
{

}
void CSliceGridItem::onState(const CGridItemData &data)
{
    m_data.pos = data.pos;
    m_data.size = data.size;

    m_property.setupProperty(&m_data);
}

void CSliceGridItem::showProperty(QtTreePropertyBrowser *treeProperty)
{
    m_property.bindProperty(treeProperty);
}

void CSliceGridItem::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式

    QRect rt(QRect(0,0,this->width(),this->height()));

    painter.drawRect(rt);
}
