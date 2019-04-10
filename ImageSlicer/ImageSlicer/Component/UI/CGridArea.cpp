#include "CGridArea.h"
#include <QPainter>
#include <QMouseEvent>

#include <cmath>
#include "Modules/SlicePanel/Component/ImgAttrListItem.h"

static const int PEN_SIZE = 1;

template<typename T>
T limitValue(T src, T min, T max)
{
    src = (src > max) ? max : src;
    src = (src < min) ? min : src;
    return src;
}

//////////////////////////////////////////////////////////////////////
CGridItemData::CGridItemData()
{

}

CGridItemData::CGridItemData(const QRect &rt):pos(rt.x(),rt.y()),size(rt.width(),rt.height())
{

}

CGridItemData::CGridItemData(int x,int y,int w,int h):pos(x,y),size(w,h)
{

}

////////

const CGridArea::LItemCreator CGridArea::defaultCreator = [](QWidget *parent)
{
    return new CGridItem(parent);
};

const CGridArea::LItemDestroyer CGridArea::defaultDestroyer = [](CGridItem *widget)
{
    delete widget;
};


CGridArea::CGridArea(QWidget *parent) : QWidget(parent),m_scale(1.0,1.0),m_creator(defaultCreator),m_destroyer(defaultDestroyer)
{

}

void CGridArea::sliceGridsBySize(const QSize &size)
{
   sliceGrids(nullptr,size);
}

void CGridArea::sliceGridsByPath(const QPoint &rw)
{
//    //四舍五入,只能牺牲中间的
//    removeAllGridItems();

//    int finalRow = limitValue(rw.x(),1,width());
//    int finalCol = limitValue(rw.y(),1,height());

//    int middleRow = (finalRow % 2 == 1) ? (finalRow/2 + 1) : (finalRow);
//    int middleCol = (finalCol % 2 == 1) ? (finalCol/2 + 1) : (finalCol);

//    int itemHeight = static_cast<int>(::round(height()/finalCol));
//    int itemWidth = static_cast<int>(::round(width()/finalRow));

//    int middleHeight = itemHeight + height() - finalCol * itemHeight;
//    int middleWidth = itemWidth + width() - finalRow * itemWidth;

//    int finalWidth = itemWidth;
//    int finalHeight = itemHeight;
//    for (int i = 0; i < width(); i+=finalWidth)
//    {
//        finalWidth = ((i + 1) == middleRow) ? middleWidth : itemWidth;
//        for (int j = 0; j < height(); j+=finalHeight)
//        {
//            finalHeight = ((j + 1) == middleCol) ? middleHeight : itemHeight;
//            CGridItemData itemData(i,j,finalWidth,finalHeight);
//            addGridItem(itemData);
//        }
//    }
//    update();

    sliceGrids(nullptr,QSizeF(width()/rw.x(),height()/rw.y()));
}

void CGridArea::sliceGrids(CGridItem *item,const QSizeF &size)
{
    if (item != nullptr)    //嵌套切割
    {

    }
    else    //完全切割
    {
        //TODO:
        removeAllGridItems();

        int finalWidth = limitValue(static_cast<int>(size.width()),1,width());
        int finalHeight = limitValue(static_cast<int>(size.height()),1,height());
        for (int j = 0; j < height(); j+=finalHeight)
        {
    //        finalHeight = (j + finalHeight > height()) ? (height() - j) : finalHeight;
            for (int i = 0; i < width(); i+=finalWidth)
            {
    //            finalWidth = (i + finalWidth > width()) ? (width() - i) : finalWidth;
                CGridItemData itemData(i,j,finalWidth,finalHeight);
                addGridItem(itemData);

            }
        }
        update();
    }
}

void CGridArea::mergeGrids(QLinkedList<CGridItem *> &list)
{
    //TODO:
}

void CGridArea::deleteGrids(QLinkedList<CGridItem *> &list)
{
    //TODO:
}

CGridItem *CGridArea::addGridItem(const CGridItemData &data)
{
    CGridItem *item = m_creator(this);
    item->setData(data);

    m_itesList.push_back(item);

    connect(item,&CGridItem::clicked,this,&CGridArea::itemClick);
    connect(this,&CGridArea::sizeChanged,item,&CGridItem::changeSize);

    return item;
}
void CGridArea::removeGridItem(CGridItem *item)
{
    //TODO:
}

void CGridArea::removeAllGridItems()
{
    for(auto it : m_itesList)
    {
        disconnect(it,&CGridItem::clicked,this,&CGridArea::itemClick);
        disconnect(this,&CGridArea::sizeChanged,it,&CGridItem::changeSize);
        m_destroyer(it);
    }
    m_itesList.clear();
}
const QLinkedList<CGridItem *> *CGridArea::getGirds() const
{
    return &m_itesList;
}

int CGridArea::getSliceCount() const
{
    return getGirds()->count();
}
///
void CGridArea::setItemCreator(LItemCreator func)
{
    m_creator = func;
}
void CGridArea::setItemDestroyer(LItemCreator func)
{
    m_destroyer = func;
}
///
void CGridArea::resetIds()
{
    //左上角开始编号
    for(auto it : m_itesList)
    {

    }
}

///
void CGridArea::itemClick(CGridItem *item)
{
    //处理代码
    emit gridClicked(item);
}

void CGridArea::paintEvent(QPaintEvent *event)
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
    show(); //理论上有parent的不需要再show(),这里不知为何只有show()才行
}

void CGridItem::setData(const CGridItemData &data)
{
    m_data = data;

    this->setGeometry(QRect(data.pos,data.size));
    this->update();

    this->onState(m_data);
}

const CGridItemData &CGridItem::getData() const
{
    return m_data;
}

void CGridItem::setUserData(void *pUserData)
{
    m_pUserData = pUserData;
}

void *CGridItem::getUserData() const
{
    return m_pUserData;
}

int CGridItem::getID()
{
    return m_id;
}
void CGridItem::setID(int id)
{
    m_id = id;
}
///
void CGridItem::onState(const CGridItemData &data)
{

}

void CGridItem::onClick()
{

}

void CGridItem::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,PEN_SIZE,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(QColor(0,0,0,0)));//设置画刷形式

    QRect rt(QRect(0,0,this->width(),this->height()));

    painter.drawRect(rt);
}

void CGridItem::changeSize(const QPointF &rate)
{
    QRect rt(static_cast<int>(this->getData().pos.x() * rate.x()),
             static_cast<int>(this->getData().pos.y() * rate.y()),
             static_cast<int>(this->getData().size.width() * rate.x()),
             static_cast<int>(this->getData().size.height() * rate.y()));
    this->setGeometry(rt);
    this->update();
}


void CGridItem::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
         m_mouserPos = QPoint(e->x(), e->y());
    }
    else
    {
        QWidget::mousePressEvent(e);
    }
}

void CGridItem::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() ==Qt::LeftButton)
    {
        this->onClick();
        emit clicked(this);
    }
    else
    {
        QWidget::mouseReleaseEvent(e);
    }
}

