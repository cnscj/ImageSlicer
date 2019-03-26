#include "CGridArea.h"
#include <QPainter>
#include <QMouseEvent>

CGridArea::CGridArea(QWidget *parent) : QWidget(parent)
{

}



void CGridArea::sliceGrids(const QSize &size)
{
    int itemWidth = (size.width() > width() ) ? width() : size.width();
    int itemHeight =(size.width() > height() ) ? height() : size.height();

    int row = height() / itemHeight;
    int col = width() / itemWidth;

    sliceGrids(row,col);
}

void CGridArea::sliceGrids(uint row,uint col)
{
    clearAllGrids();

    row = (row > height()) ? height() : row;
    col = (col > width()) ? width() : col;

    int itemWidth = width()/col;
    int itemHeight = height()/row;

    for (int i = 0; i<row; i++)
    {
        for (int j = 0; j<col; j++)
        {
            CGridItem *item = new CGridItem(this);
            CGridItem::CData data;
            data.pos = QPoint(itemWidth * j,itemHeight * i);
            data.size = QSize(itemWidth,itemHeight);
            item->setData(data);

            m_itesList.push_back(item);
            item->update();

            connect(item,SIGNAL(clicked(CGridItem *)),this,SLOT(itemClick(CGridItem *)));
            connect(this,SIGNAL(sizeChanged(QPointF )),item,SLOT(changeSize(QPointF )));
        }
    }
}
void CGridArea::mergeGrids()
{

}

void CGridArea::clearAllGrids()
{
    for(auto it : m_itesList)
    {
        disconnect(it,SIGNAL(clicked(CGridItem *)),this,SLOT(itemClick(CGridItem *)));
        disconnect(this,SIGNAL(sizeChanged(QPointF )),it,SLOT(changeSize(QPointF )));
        it->deleteLater();
    }
}
const QLinkedList<CGridArea::CGridItem *> &CGridArea::getGirds() const
{
    return m_itesList;
}

///
void CGridArea::itemClick(CGridArea::CGridItem *item)
{
    //处理代码

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
    double rateX = (newSizeWidth/oldSizeWidth);
    double rateY = (newSizeHeight/oldSizeHeight);

    emit sizeChanged(QPointF(rateX,rateY));
    QWidget::resizeEvent(event);
}





/////////////////////
/////////////////////
CGridArea::CGridItem::CGridItem(QWidget *parent) : QWidget(parent)
{

}

void CGridArea::CGridItem::setData(const CGridArea::CGridItem::CData &data)
{
    m_data = data;
    this->setGeometry(QRect(data.pos,data.size));
}
const CGridArea::CGridItem::CData &CGridArea::CGridItem::getData() const
{
    return m_data;
}

void CGridArea::CGridItem::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式
//    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式

    QRect rt(QRect(0,0,this->width(),this->height()));
    painter.drawRect(rt);

}

void CGridArea::CGridItem::changeSize(QPointF rate)
{
    //TODO:算法
    QRect rt(this->pos().x() * rate.x() ,this->pos().y() * rate.y(),
          this->size().width() * rate.x() , this->size().height() * rate.y());

    this->setGeometry(rt);
    this->update();
}


void CGridArea::CGridItem::mousePressEvent(QMouseEvent *e)
{
    m_mouserPos = QPoint(e->x(), e->y());
}

void CGridArea::CGridItem::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    emit clicked(this);

}




//////////////////
///////
///
///
