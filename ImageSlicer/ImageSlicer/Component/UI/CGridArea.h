#ifndef CGRIDAREA_H
#define CGRIDAREA_H

#include <QWidget>
#include <QLinkedList>
class QMouseEvent;

class CGridArea;
class CGridItem;
class CGridItemData;

class CGridItemData
{
public:
    QPoint pos;
    QSize size;

};

class CGridArea : public QWidget
{
    Q_OBJECT
public:
    CGridArea(QWidget *parent = nullptr);
public slots:
    void itemClick(CGridItem *);
public:
    void sliceGrids(const QSize &size);
    void sliceGrids(int row,int col);
    void mergeGrids();

    void clearAllGrids();

    const QLinkedList<CGridItem *> &getGirds() const;
signals:
    void sizeChanged(const QPointF &);
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
private:
    QLinkedList<CGridItem *> m_itesList;
    QPointF m_scale;
};



class CGridItem : public QWidget
{
    Q_OBJECT
public:
    CGridItem(QWidget *parent = nullptr);
public:
    void setData(const CGridItemData &);
    const CGridItemData &getData()const;
signals:
    void clicked(CGridItem *);
public slots:
    void changeSize(const QPointF &);
protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QPoint m_mouserPos;
    CGridItemData m_data;
};

#endif // CGRIDAREA_H
