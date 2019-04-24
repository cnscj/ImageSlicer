#ifndef CSLICEGRIDSDATA_H
#define CSLICEGRIDSDATA_H

#include <QString>
class CSliceGridsData
{
public:
    QString names;
    bool enables;

    QString remarks;
    int offsetX;
    int offsetY;

public:
    CSliceGridsData();
};

#endif // CSLICEGRIDSDATA_H
