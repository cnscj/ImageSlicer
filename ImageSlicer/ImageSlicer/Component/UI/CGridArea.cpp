#include "CGridArea.h"
#include <QPainter>
#include <QMouseEvent>
CGridItemData::CGridItemData()
{

}
CGridItemData::CGridItemData(const QRect &rt):pos(rt.x(),rt.y()),size(rt.width(),rt.height())
{

}
CGridItemData::CGridItemData(int x,int y,int w,int h):pos(x,y),size(w,h)
{

}

CGridArea::CGridArea(QWidget *parent) : QWidget(parent),m_scale(1.0,1.0)
{

}

void CGridArea::sliceGrids(const QSize &size)
{
    //TODO:切割算法:不足size的按剩余的切
    removeAllGrids();

    float itemWidth = ( size.width() > width() ) ? width() : size.width();
    float itemHeight = ( size.width() > height() ) ? height() : size.height();

    qDebug("切割大小:(%d,%d)",itemWidth,itemHeight);

    //TODO:
}

void CGridArea::sliceGrids(const QPoint &rw)
{
    //TODO:按靠近SIze大小切,只能牺牲中间的
    removeAllGrids();

    int finalRow = (rw.x() > width()) ? width() : rw.x();
    int finalCol = (rw.y() > height()) ? height() : rw.y();

    int itemWidth = height()/finalCol;
    int itemHeight = width()/finalRow;


    //TODO:
//    for (int i = 0; i < finalRow; i++)
//    {
//        for (int j = 0; j < finalCol; j++)
//        {
//            CGridItemData itemData(i*itemWidth,j*itemHeight,itemWidth,itemHeight);
//            addGridItem(itemData);
//        }
//    }
//    update();
}
void CGridArea::mergeGrids()
{

}

CGridItem *CGridArea::addGridItem(const CGridItemData &data)
{
    CGridItem *item = new CGridItem(this);
    item->setData(data);

    m_itesList.push_back(item);

    connect(item,&CGridItem::clicked,this,&CGridArea::itemClick);
    connect(this,&CGridArea::sizeChanged,item,&CGridItem::changeSize);

    return item;
}

void CGridArea::removeAllGrids()
{
    for(auto it : m_itesList)
    {
        disconnect(it,&CGridItem::clicked,this,&CGridArea::itemClick);
        disconnect(this,&CGridArea::sizeChanged,it,&CGridItem::changeSize);
        it->deleteLater();
    }
    m_itesList.clear();
}
const QLinkedList<CGridItem *> &CGridArea::getGirds() const
{
    return m_itesList;
}

///
void CGridArea::itemClick(CGridItem *item)
{
    //处理代码
    qDebug("%d_%d_%d_%d",item->getData().pos.x(),item->getData().pos.y(),item->getData().size.width(),item->getData().size.height());
}

void CGridArea::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
}

void CGridArea::resizeEvent(QResizeEvent *event)
{
    double newSizeWidth = event->size().width();
    double oldSizeWidth = event->oldSize().width() > 0 ? event->oldSize().width() : newSizeWidth;
    double newSizeHeight = event->size().width();
    double oldSizeHeight = event->oldSize().height() > 0 ? event->oldSize().height() : newSizeHeight;
    m_scale.setX((newSizeWidth/oldSizeWidth) * m_scale.x());
    m_scale.setY((newSizeHeight/oldSizeHeight) * m_scale.y());

    emit sizeChanged(m_scale);
    QWidget::resizeEvent(event);
}





/////////////////////
/////////////////////
CGridItem::CGridItem(QWidget *parent) : QWidget(parent)
{

}

void CGridItem::setData(const CGridItemData &data)
{
    m_data = data;
    this->setGeometry(QRect(data.pos,data.size));
    this->update();
}
const CGridItemData &CGridItem::getData() const
{
    return m_data;
}

void CGridItem::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));//设置画笔形式
//    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式

    QRect rt(QRect(0,0,this->width(),this->height()));
    painter.drawRect(rt);

}

void CGridItem::changeSize(const QPointF &rate)
{
    QRect rt(this->getData().pos.x() * rate.x() ,this->getData().pos.y() * rate.y(),
          this->getData().size.width() * rate.x() , this->getData().size.height() * rate.y());

    this->setGeometry(rt);
    this->update();
}


void CGridItem::mousePressEvent(QMouseEvent *e)
{
    m_mouserPos = QPoint(e->x(), e->y());
}

void CGridItem::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    emit clicked(this);

}




//////////////////
///////
///
///
