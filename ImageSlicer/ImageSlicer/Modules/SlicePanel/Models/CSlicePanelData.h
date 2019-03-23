#ifndef CSLICEPANELDATA_H
#define CSLICEPANELDATA_H
#include <QLinkedList>
#include "CSliceGridData.h"

uint qHash(const CSliceGridData *&pData, uint seed = 0)
{
    return pData->getUID();
}

class CSlicePanelData
{
public:
    int sliceRow;       //横向数
    int sliceCol;       //纵向数

    QLinkedList<CSliceGridData *> m_gridList;//格子数组
public:
    void mergeGrids(const QSet<CSliceGridData> &);
public:
    CSlicePanelData();
};

#endif // CSLICEPANELDATA_H
