#ifndef CSLICEGRIDDATA_H
#define CSLICEGRIDDATA_H
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QString>

#include "Component/UI/CGridArea.h"
class CSliceGridData
{
public:
    bool enable;
    QString name;
    QString extra;
    QString description;

    QPoint pos;
    QSize size;
    QPointF center;
public:
    uint getUID() const;
    QRect getRect() const;
    CGridItemData getOriData();
public:
    bool operator <(const CSliceGridData &) const;
    bool operator ==(const CSliceGridData &) const;
public:
    CSliceGridData();
};

#endif // CSLICEGRIDDATA_H
