#include "CSliceGridItem.h"
#include <QPainter>

static const int PEN_SIZE = 1;
static const QPen DEFAULE_PEN = QPen(Qt::blue,PEN_SIZE,Qt::SolidLine);

CSliceGridItem::CSliceGridItem(QWidget *parent) : CGridItem(parent), m_isSelected(false),m_pen(DEFAULE_PEN)
{

}
CSliceGridItem::~CSliceGridItem()
{
    disconnect(&m_property,&CSliceGridProperty::dataChanged,this,&CSliceGridItem::propValueChanged);
}

void CSliceGridItem::onState(const CGridItemData &data)
{
    CSliceGridData itemData;
    itemData.enable = true;
    itemData.name = "";   //TODO:名字理论上是
    itemData.remark = "";

    itemData.pos = data.pos;
    itemData.size = data.size;

    m_property.setData(itemData);
    connect(&m_property,&CSliceGridProperty::dataChanged,this,&CSliceGridItem::propValueChanged);
}

void CSliceGridItem::showProperty(QtTreePropertyBrowser *treeProperty)
{
    m_property.bindProperty(treeProperty);
}

void CSliceGridItem::onSelected(bool isSelected)
{
    m_isSelected = isSelected;
    if (isSelected)
    {
        m_pen = QPen(Qt::red,PEN_SIZE,Qt::SolidLine);
    }else
    {
        m_pen = DEFAULE_PEN;
    }
    this->update();
}

void CSliceGridItem::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setPen(m_pen);//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式

    QRect rt(QRect(0,0,this->width(),this->height()));

    painter.drawRect(rt);

    //TODO:显示id
}

void CSliceGridItem::propValueChanged(const QString &propName,const CSliceGridData &data)
{
    if (propName == "enable")
    {
        if (data.enable)
        {
            m_pen = DEFAULE_PEN;
        }
        else
        {
            m_pen = QPen(Qt::black,PEN_SIZE,Qt::SolidLine);
        }
        this->update();
    }
}
