#ifndef CSLICEGRIDDATA_H
#define CSLICEGRIDDATA_H
#include <QPoint>
#include <QSize>

class CSliceGridData
{
public:
    QPoint pos;
    QSize size;
    bool enable;

public:
    bool operator < (const CSliceGridData &data);

public:
    CSliceGridData();
};

#endif // CSLICEGRIDDATA_H
