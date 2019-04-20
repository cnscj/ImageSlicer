#include "CGridArea.h"
#include <QPainter>
#include <QMouseEvent>

#include <cmath>
#include "Modules/SlicePanel/Component/ImgAttrListItem.h"

static const int PEN_SIZE = 1;

template<typename T>
static T limitValue(T src, T min, T max)
{
    src = (src > max) ? max : src;
    src = (src < min) ? min : src;
    return src;
}

static bool sortItemByPos(const CGridItem *a,const CGridItem *b)
{
    if (a->getData().pos.y() == b->getData().pos.y())
    {
        return (a->getData().pos.x() < b->getData().pos.x());
    }
    return (a->getData().pos.y() < b->getData().pos.y());
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

QRect CGridItemData::rect() const
{
    return QRect(pos,size);
}
void CGridItemData::setRect(const QRect &rt)
{
    pos = QPoint(rt.x(),rt.y());
    size = QSize(rt.width(),rt.height());
}
////////

const CGridArea::LItemCreator CGridArea::defaultCreator = [](const CGridItemData &data)
{
    Q_UNUSED(data);
    auto item = new CGridItem();
    return item;
};

const CGridArea::LItemDestroyer CGridArea::defaultDestroyer = [](CGridItem *widget)
{
    delete widget;
};


CGridArea::CGridArea(QWidget *parent) : QWidget(parent),
    m_scale(1.0,1.0),m_creator(defaultCreator),
    m_destroyer(defaultDestroyer),m_selectMode(ESelectMode::None)
{

}

void CGridArea::sliceGrids(CGridItem *item,const QSizeF &size)
{
    if (item != nullptr)    //嵌套切割
    {
        auto startPos = item->getData().pos;
        auto oriSize = item->getData().size;
        int finalWidth = limitValue(static_cast<int>(size.width()),1,oriSize.width());
        int finalHeight = limitValue(static_cast<int>(size.height()),1,oriSize.height());

        for (int j = 0; j < oriSize.height(); j+=finalHeight)
        {
            for (int i = 0; i < oriSize.width(); i+=finalWidth)
            {
                CGridItemData itemData(startPos.x() + i,startPos.y() + j,finalWidth,finalHeight);
                addGridItem(itemData);
            }
        }
        removeGridItem(item);
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
    }
    resetIds();

    emit sizeChanged(m_scale);
}

void CGridArea::mergeGrids(const QList<CGridItem *> &list)
{
    if (list.count() > 1)
    {
        QPoint minLTPos(INT_MAX,INT_MAX);        //找出最左上角的点
        QPoint maxRBPos(INT_MIN,INT_MIN);       //找出最右下角的点
        for(auto it : list)
        {
            if (it->getData().pos.x() < minLTPos.x())
            {
                minLTPos.setX(it->getData().pos.x());
            }
            if (it->getData().pos.y() < minLTPos.y())
            {
                minLTPos.setY(it->getData().pos.y());
            }

            QPoint widgetRBPos(it->getData().pos.x() + it->getData().size.width(),it->getData().pos.y() + it->getData().size.height());
            if (widgetRBPos.x() > maxRBPos.x())
            {
                maxRBPos.setX(widgetRBPos.x());
            }
            if (widgetRBPos.y() > maxRBPos.y())
            {
                maxRBPos.setY(widgetRBPos.y());
            }
        }
        QRect retRt = QRect(minLTPos.x(),minLTPos.y(),maxRBPos.x()-minLTPos.x(),maxRBPos.y()-minLTPos.y());
        qDebug(QString("%1,%2,%3,%4").arg(retRt.x()).arg(retRt.y()).arg(retRt.width()).arg(retRt.height()).toStdString().c_str());

        //移除在这个区域没得图形
        removeGrids(list);
        for (auto it : m_itemsList)
        {
           if (retRt.contains(it->getData().rect()))    //TODO:因为有极小的误差导致删不掉
           {
               removeGridItem(it);
           }
        }

        //添加
        CGridItemData data;
        data.setRect(retRt);
        addGridItem(data);

        resetIds();

        emit sizeChanged(m_scale);
    }
}

void CGridArea::removeGrids(const QList<CGridItem *> &list)
{
    for(auto it : list)
    {
        removeGridItem(it);
    }

    resetIds();

    emit sizeChanged(m_scale);
}

CGridItem *CGridArea::addGridItem(const CGridItemData &data)
{
    CGridItem *item = m_creator(data);
    item->setParent(this);
    item->setData(data);
    item->setVisible(true);
    item->show();

    m_itemsList.push_back(item);

    connect(item,&CGridItem::clicked,this,&CGridArea::itemClick);
    connect(this,&CGridArea::sizeChanged,item,&CGridItem::changeSize);

    return item;
}
void CGridArea::removeGridItem(CGridItem *item)
{
    if (item)
    {
        removeSelectList(item);

        disconnect(item,&CGridItem::clicked,this,&CGridArea::itemClick);
        disconnect(this,&CGridArea::sizeChanged,item,&CGridItem::changeSize);

        m_itemsList.removeOne(item);
        m_destroyer(item);
    }
}

void CGridArea::removeAllGridItems()
{
    for(auto it : m_itemsList)
    {
        removeGridItem(it);
    }
    m_itemsList.clear();
}
const QList<CGridItem *> *CGridArea::getGirds() const
{
    return &m_itemsList;
}

int CGridArea::getSliceCount() const
{
    return getGirds()->count();
}
void CGridArea::addSelectList(CGridItem *item, bool isCheck)
{
    if (isCheck)
    {
        if (item->isSelected())
        {
            removeSelectList(item);
        }
        else
        {
            m_selectList.push_back(item);
            item->setSelected(true);
        }
    }
    else
    {
        if (!item->isSelected())
        {
            m_selectList.push_back(item);
            item->setSelected(true);
        }
    }
}
const QList<CGridItem *> &CGridArea::getSelectList()
{
    return m_selectList;
}

void CGridArea::removeSelectList(CGridItem *item)
{
    item->setSelected(false);
    m_selectList.removeOne(item);
}
void CGridArea::clearSelectList()
{
    for (auto it : m_selectList)
    {
        removeSelectList(it);
    }
    m_selectList.clear();
}

void CGridArea::setSelectMode(ESelectMode mode)
{
    m_selectMode = mode;
}
CGridArea::ESelectMode CGridArea::getSelectMode()
{
    return m_selectMode;
}
///
void CGridArea::setItemCreator(LItemCreator func)
{
    m_creator = func;
}

void CGridArea::setItemDestroyer(LItemDestroyer func)
{
    m_destroyer = func;
}

const CGridArea::LItemCreator &CGridArea::getItemCreator()
{
    return m_creator;
}
const CGridArea::LItemDestroyer &CGridArea::getItemDestroyer()
{
    return m_destroyer;
}
///
void CGridArea::reset()
{
    m_scale = QPointF(1.0,1.0);
}
void CGridArea::resetIds()
{
    //左上角开始编号
    QList<CGridItem *> itemsList = m_itemsList;
    std::sort(itemsList.begin(),itemsList.end(),sortItemByPos);

    int id = 0;
    for(auto it : itemsList)
    {
        it->setIndex(++id);
    }
}
void CGridArea::adjust()
{
    emit sizeChanged(m_scale);
}

///
void CGridArea::itemClick(CGridItem *item)
{
    if (m_selectMode == ESelectMode::Single)
    {
        //取消掉之前所有选择,再选
        clearSelectList();
        addSelectList(item);
    }
    else if(m_selectMode == ESelectMode::Multiple)
    {
        //直接加入选择列表
        addSelectList(item);
    }

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

CGridItem::CGridItem(QWidget *parent) : QWidget(parent),m_scale(1.0,1.0),m_pUserData(nullptr),m_isSelected(false)
{
    //不能再这里show(),会疯狂闪
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

CGridItemData *CGridItem::getDataPtr()
{
     return &m_data;
}

void CGridItem::setUserData(void *pUserData)
{
    m_pUserData = pUserData;
}

void *CGridItem::getUserData() const
{
    return m_pUserData;
}

int CGridItem::getIndex()
{
    return m_index;
}
void CGridItem::setIndex(int index)
{
    m_index = index;
    onIndex(index);
}
bool CGridItem::isSelected()
{
    return m_isSelected;
}
void CGridItem::setSelected(bool isSelected)
{
    m_isSelected = isSelected;
    onSelected(m_isSelected);
}

void CGridItem::updateScale()
{
    changeSize(m_scale);
}

///
void CGridItem::onState(const CGridItemData &data)
{
    Q_UNUSED(data);
}

void CGridItem::onClick()
{

}

void CGridItem::onSelected(bool isSelected)
{
    Q_UNUSED(isSelected);
}
void CGridItem::onIndex(int index)
{
    Q_UNUSED(index);
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
    m_scale = rate;
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

