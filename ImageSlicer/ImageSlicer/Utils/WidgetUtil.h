#ifndef WIDGETUTIL_H
#define WIDGETUTIL_H

#include <QWidget>

class WidgetUtil
{
public:
    class CDebugNode;
public:
    static bool isCursorInWidget(const QWidget *);  //鼠标书否在控件上

private:
    WidgetUtil();
};



#endif // WIDGETUTIL_H
