#ifndef CGRIDAREA_H
#define CGRIDAREA_H

#include <QWidget>



class CGridArea : public QWidget
{
    Q_OBJECT
public:
    class CGridItem;
public:
    CGridArea(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent * event);
};


class CGridArea::CGridItem : public QWidget
{
    Q_OBJECT
public:
    CGridItem(QWidget *parent = nullptr);
};
#endif // CGRIDAREA_H
