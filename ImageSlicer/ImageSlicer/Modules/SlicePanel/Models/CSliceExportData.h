#ifndef CSLICEEXPORTDATA_H
#define CSLICEEXPORTDATA_H

#include <QList>
#include "CSlicePanelData.h"
#include "CSliceGridData.h"
class CSliceExportData
{
public:
    CSlicePanelData *panelData;
    QList<CSliceGridData *> gridsList;
public:
    CSliceExportData();
};

#endif // CSLICEEXPORTDATA_H
