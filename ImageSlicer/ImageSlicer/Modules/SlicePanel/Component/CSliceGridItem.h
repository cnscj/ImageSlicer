#ifndef CSLICEGRIDITEM_H
#define CSLICEGRIDITEM_H
#include <QWidget>
#include <QtVariantPropertyManager>
#include "Component/UI/CGridArea.h"
#include "../Models/CSliceGridData.h"
#include "../Models/CSliceGridProperty.h"

class CSliceGridItem : public CGridItem
{
    Q_OBJECT
public:
    CSliceGridItem(QWidget *parent = nullptr);
public:
    void showProperty(QtTreePropertyBrowser *treeProperty);
protected:
    void onState(const CGridItemData &data);
    void paintEvent(QPaintEvent *e);
private:
    CSliceGridData m_data;
    CSliceGridProperty m_property;

};

#endif // CSLICEGRIDITEM_H
