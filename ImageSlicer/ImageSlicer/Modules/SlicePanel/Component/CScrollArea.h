#ifndef CSCROLLAREA_H
#define CSCROLLAREA_H

#include <QScrollArea>
class QWheelEvent;

class CScrollArea : public QScrollArea
{
public:
    explicit CScrollArea(QWidget *parent = nullptr);
    ~CScrollArea();
public:
    void setWheelScrollEnable(bool isEnable);
    bool isWheelScrollEnabled();

protected:
    virtual void wheelEvent(QWheelEvent * e);           //滚轮事件
private:
    bool m_isWheelEnable;
};

#endif // CSCROLLAREA_H
