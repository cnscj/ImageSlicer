#ifndef CSLICEGRIDDATA_H
#define CSLICEGRIDDATA_H
#include <QPoint>
#include <QSize>
#include <QRect>

class CSliceGridData
{
public:
    QPoint pos;
    QSize size;
    bool enable;
public:
    uint getUID() const;
    QRect getRect() const;
public:
    bool operator <(const CSliceGridData &) const;
    bool operator ==(const CSliceGridData &) const;
public:
    CSliceGridData();
};

#endif // CSLICEGRIDDATA_H
