#include "WidgetUtil.h"
#include <QWidget>
#include <QCursor>
#include <QPainter>

////////////

bool WidgetUtil::isCursorInWidget(const QWidget *widget)
{
    return widget->geometry().contains(widget->mapFromGlobal(QCursor::pos()));
}



WidgetUtil::WidgetUtil()
{

}
