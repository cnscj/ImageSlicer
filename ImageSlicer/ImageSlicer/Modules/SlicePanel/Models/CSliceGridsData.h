#ifndef CSLICEGRIDSDATA_H
#define CSLICEGRIDSDATA_H

#include <QString>
class CSliceGridsData
{
public:
    QString names;
    bool enables;
    QString extras;
    QString descriptions;

    int offsetX;
    int offsetY;

public:
    CSliceGridsData();
};

#endif // CSLICEGRIDSDATA_H
