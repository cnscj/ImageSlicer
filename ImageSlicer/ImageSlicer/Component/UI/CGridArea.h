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
    QRect rect() const;
    void setRect(const QRect &);
public:
    CGridItemData();
    CGridItemData(const QRect &);
    CGridItemData(int x,int y,int w,int h);
};

class CGridArea : public QWidget
{
    Q_OBJECT
public:
    typedef std::function<CGridItem *(const CGridItemData &data)> LItemCreator;
    typedef std::function<void(CGridItem *)> LItemDestroyer;

    static const LItemCreator defaultCreator;
    static const LItemDestroyer defaultDestroyer;

    enum class ESelectMode{None,Single,Multiple,Continuous};
public:
    CGridArea(QWidget *parent = nullptr);
    ~CGridArea();
public slots:
    void itemClick(CGridItem *);
public:
    void sliceGrids(const QList<CGridItem *> &list,const QSizeF &size);
    void mergeGrids(const QList<CGridItem *> &list);
    void removeGrids(const QList<CGridItem *> &list);

    CGridItem *addGridItem(const CGridItemData &data);
    void removeGridItem(CGridItem *item);
    void removeAllGridItems();
    const QList<CGridItem *> *getGirds() const;

    int getSliceCount() const;

    void addSelectList(CGridItem *item, bool isCheck = true);
    void removeSelectList(CGridItem *item);
    const QList<CGridItem *> &getSelectList();
    void clearSelectList();

    void setSelectMode(ESelectMode mode);
    ESelectMode getSelectMode();
public:
    void setItemCreator(LItemCreator);
    void setItemDestroyer(LItemDestroyer);

    const LItemCreator &getItemCreator();
    const LItemDestroyer &getItemDestroyer();
signals:
    void sizeChanged(const QPointF &);
    void gridClicked(CGridItem *);
public:
    void reset();
    void resetIds();
    void adjust();
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
private:
    QList<CGridItem *> m_itemsList;
    QPointF m_scale;
    LItemCreator m_creator;
    LItemDestroyer m_destroyer;

    ESelectMode m_selectMode;
    QList<CGridItem *> m_selectList;

};

class CGridItem : public QWidget
{
    Q_OBJECT
public:
    friend class CGridArea;
public:
    CGridItem(QWidget *parent = nullptr);
    virtual ~CGridItem();
public:
    void setData(const CGridItemData &);
    const CGridItemData &getData()const;
    CGridItemData *getDataPtr();

    void setUserData(void *pUserData);
    void *getUserData() const;

    int getIndex() const;
    bool isSelected();


    void updateScale();
signals:
    void clicked(CGridItem *);
public slots:
    void changeSize(const QPointF &);

protected:
    virtual void onState(const CGridItemData &data);
    virtual void onClick();
    virtual void onSelected(bool isSelected);
    virtual void onIndex(int index);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void setIndex(int id);
    void setSelected(bool isSelected);

protected:
    CGridItemData m_data;
private:
    QPoint m_mouserPos;
    QPointF m_scale;

    void *m_pUserData;
    bool m_isSelected;

    int m_index = -1;
};

#endif // CGRIDAREA_H
