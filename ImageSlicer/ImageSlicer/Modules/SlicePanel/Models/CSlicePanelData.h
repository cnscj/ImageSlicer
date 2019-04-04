#ifndef CSLICEPANELDATA_H
#define CSLICEPANELDATA_H
#include <QLinkedList>
#include "CSliceGridData.h"

uint qHash(const CSliceGridData *&pData)
{
    return pData->getUID();
}

class CSlicePanelData
{
public:

    QLinkedList<CSliceGridData *> m_gridList;//格子数组
public:
    void mergeGrids(const QSet<CSliceGridData> &);
public:
    CSlicePanelData();
};

#endif // CSLICEPANELDATA_H
