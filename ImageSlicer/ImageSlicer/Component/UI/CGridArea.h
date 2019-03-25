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
public:
    void setScale(double scale);
    double getScale();
public:
    void mergeGrids();
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
private:
    double m_scale;
    QLinkedList<CGridItem *> m_itesList;
};


class CGridArea::CGridItem : public QWidget
{
    Q_OBJECT
public:
    CGridItem(QWidget *parent = nullptr);
signals:
    void clicked();
public slots:
    void mouseClicked();
protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);
private:
    QPoint m_mouserPos;

};
#endif // CGRIDAREA_H
