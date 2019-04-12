#ifndef CSLICERESULTDATA_H
#define CSLICERESULTDATA_H
#include <QList>
#include "CSlicePanelData.h"
#include "CSliceGridData.h"
class CSliceResultData
{
public:
    CSlicePanelData *panelData;
    QList<CSliceGridData *> gridsList;
public:
    CSliceResultData();
};

#endif // CSLICERESULTDATA_H
