#include "CSliceGridItem.h"
#include <QPainter>

static const int PEN_SIZE = 1;
static const QPen DEFAULE_PEN = QPen(Qt::blue,PEN_SIZE,Qt::SolidLine);
static const QPen SELECTED_PEN = QPen(Qt::red,PEN_SIZE,Qt::SolidLine);
static const QPen SELECTED_INVAILD_PEN = QPen(Qt::darkRed,PEN_SIZE,Qt::SolidLine);
static const QPen INVAILD_PEN = QPen(Qt::black,PEN_SIZE,Qt::SolidLine);

CSliceGridItem::CSliceGridItem(QWidget *parent) : CGridItem(parent),m_fileName(""),m_pen(DEFAULE_PEN), m_isSelected(false)
{

}
CSliceGridItem::~CSliceGridItem()
{
    disconnect(&m_property,&CSliceGridProperty::dataChanged,this,&CSliceGridItem::propValueChanged);
}

void CSliceGridItem::showProperty(QtTreePropertyBrowser *treeProperty)
{
    m_property.bindProperty(treeProperty);
}

CSliceGridData *CSliceGridItem::getPropertyData()
{
    return &m_property.getData();
}

void CSliceGridItem::setFileName(const QString &name)
{
    m_fileName = name;
}
const QString &CSliceGridItem::getFileName()
{
    return m_fileName;
}

void CSliceGridItem::onState(const CGridItemData &data)
{
    CSliceGridData itemData;
    itemData.enable = true;
    itemData.name = "";
    itemData.remark = "";

    itemData.pos = data.pos;
    itemData.size = data.size;

    m_property.setData(itemData);
    connect(&m_property,&CSliceGridProperty::dataChanged,this,&CSliceGridItem::propValueChanged);
}

void CSliceGridItem::onSelected(bool isSelected)
{
    m_isSelected = isSelected;
    if (isSelected)
    {
        if (m_property.getData().enable)
        {
            m_pen = SELECTED_PEN;
        }
        else
        {
            m_pen = SELECTED_INVAILD_PEN;
        }

    }
    else
    {
        if (m_property.getData().enable)
        {
            m_pen = DEFAULE_PEN;
        }
        else
        {
            m_pen = INVAILD_PEN;
        }
    }
    this->update();
}
void CSliceGridItem::onIndex(int index)
{
    auto data = m_property.getData();
    if (data.name == "")
    {
        data.name = QString("%1_%2").arg(m_fileName).arg(index,2,10,QLatin1Char('0'));
        m_property.setData(data);
    }
}
void CSliceGridItem::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setPen(m_pen);//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式

    QRect rt(QRect(0,0,this->width(),this->height()));
    painter.drawRect(rt);

    painter.drawText(rt,Qt::AlignCenter,QString("%1").arg(getIndex()));
}

void CSliceGridItem::propValueChanged(const QString &propName,const CSliceGridData &data)
{
    if (propName == "enable")
    {
        if (data.enable)
        {
            if (this->isSelected())
            {
                m_pen = SELECTED_PEN;
            }
            else
            {
                m_pen = DEFAULE_PEN;
            }
        }
        else
        {
            if (this->isSelected())
            {
                m_pen = SELECTED_INVAILD_PEN;
            }
            else
            {
                m_pen = INVAILD_PEN;
            }

        }
        this->update();
    }
}
