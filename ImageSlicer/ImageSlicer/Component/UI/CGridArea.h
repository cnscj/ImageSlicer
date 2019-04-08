#ifndef CGRIDAREA_H
#define CGRIDAREA_H

#include <functional>
#include <QWidget>
#include <QLinkedList>

class QMouseEvent;

class CGridArea;
class CGridItem;
class CGridItemData;

//这里没有必要记录原始值,而且也没有意义
class CGridItemData
{
public:
    QPoint pos;
    QSize size;
public:
    CGridItemData();
    CGridItemData(const QRect &);
    CGridItemData(int x,int y,int w,int h);
};

class CGridArea : public QWidget
{
    Q_OBJECT
public:
    typedef std::function<CGridItem *(QWidget *parent)> LItemCreator;
    typedef std::function<void(CGridItem *)> LItemDestroyer;

    static const LItemCreator defaultCreator;
    static const LItemDestroyer defaultDestroyer;
public:
    CGridArea(QWidget *parent = nullptr);
public slots:
    void itemClick(CGridItem *);
public:
    void sliceGridsBySize(const QSize &size);
    void sliceGridsByPath(const QPoint &pt);

    void sliceGrids(CGridItem *item,const QSizeF &size);
    void mergeGrids(QLinkedList<CGridItem *> &list);
    void deleteGrids(QLinkedList<CGridItem *> &list);

    CGridItem *addGridItem(const CGridItemData &data);
    void removeGridItem(CGridItem *item);
    void removeAllGridItems();
    const QLinkedList<CGridItem *> *getGirds() const;

    int getSliceCount() const;
public:
    void setItemCreator(LItemCreator);
    void setItemDestroyer(LItemCreator);
signals:
    void sizeChanged(const QPointF &);
    void gridClicked(CGridItem *);
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
private:
    QLinkedList<CGridItem *> m_itesList;
    QPointF m_scale;
    LItemCreator m_creator;
    LItemDestroyer m_destroyer;

};



class CGridItem : public QWidget
{
    Q_OBJECT
public:
    CGridItem(QWidget *parent = nullptr);
public:
    void setData(const CGridItemData &);
    const CGridItemData &getData()const;

    void setUserData(void *pUserData);
    void *getUserData() const;
signals:
    void clicked(CGridItem *);
public slots:
    void changeSize(const QPointF &);

protected:
    virtual void onState(const CGridItemData &data);
    virtual void onClick();

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QPoint m_mouserPos;
    CGridItemData m_data;
    void *m_pUserData;
};

#endif // CGRIDAREA_H
