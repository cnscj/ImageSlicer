#ifndef DEBUGUTIL_H
#define DEBUGUTIL_H

#include <QWidget>

class DebugUtil
{
public:
    class CDrawNode;
public:
    static void drawWidget(QWidget *);        //绘制控件
public:
    DebugUtil();
};

class DebugUtil::CDrawNode : public QWidget
{
    Q_OBJECT
public:
    explicit CDrawNode(QWidget *parent = 0);
    ~CDrawNode();
protected:
    void paintEvent(QPaintEvent * event);
    bool eventFilter(QObject *target, QEvent *event);
};

#endif // DEBUGUTIL_H
