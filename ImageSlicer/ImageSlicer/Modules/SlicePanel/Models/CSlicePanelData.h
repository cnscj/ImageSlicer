#ifndef CSLICEPANELDATA_H
#define CSLICEPANELDATA_H
#include <QSet>
#include "CSliceGridData.h"

class CSlicePanelData
{
public:
    int sliceRow;       //横向数
    int sliceCol;       //纵向数

    QSet<CSliceGridData> m_gridList;//格子数组
public:
    void mergeGrids(const QSet<CSliceGridData> &);
public:
    CSlicePanelData();
};

#endif // CSLICEPANELDATA_H
