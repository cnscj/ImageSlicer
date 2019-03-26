#ifndef CGRIDAREA_H
#define CGRIDAREA_H

#include <QWidget>
#include <QLinkedList>
class QMouseEvent;

class CGridArea : public QWidget
{
    Q_OBJECT
public:
    class CGridItem;
public:
    CGridArea(QWidget *parent = nullptr);
public slots:
    void itemClick(CGridItem *);
public:
    void sliceGrids(const QSize &size);
    void sliceGrids(uint row,uint col);
    void mergeGrids();

    void clearAllGrids();

    const QLinkedList<CGridItem *> &getGirds() const;
signals:
    void sizeChanged(QPointF);
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
private:
    QLinkedList<CGridItem *> m_itesList;
};


class CGridArea::CGridItem : public QWidget
{
    Q_OBJECT
public:
    class CData
    {
        public:
            QPoint pos;
            QSize size;

    };
public:
    CGridItem(QWidget *parent = nullptr);
public:
    void setData(const CData &);
    const CData &getData()const;
signals:
    void clicked(CGridItem *);
public slots:
    void changeSize(QPointF);
protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QPoint m_mouserPos;
    CData m_data;
};


#endif // CGRIDAREA_H
