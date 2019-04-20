#ifndef CSLICEIMPORTDATA_H
#define CSLICEIMPORTDATA_H

#include <QList>
#include "CSlicePanelData.h"
#include "CSliceGridData.h"

class CSliceImportData
{
public:
    QString imagePath;
    QList<CSliceGridData *> gridsList;
public:
    CSliceImportData();
};

#endif // CSLICEIMPORTDATA_H
