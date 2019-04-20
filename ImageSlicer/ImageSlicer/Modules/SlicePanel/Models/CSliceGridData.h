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
    QString name;
    QString remark;
    bool enable;

    QPoint pos;
    QSize size;
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
