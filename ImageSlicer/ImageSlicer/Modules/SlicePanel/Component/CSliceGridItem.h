#ifndef CSLICEGRIDITEM_H
#define CSLICEGRIDITEM_H
#include <QWidget>
#include <QtVariantPropertyManager>
#include "CSliceGridProperty.h"
#include "Component/UI/CGridArea.h"
#include "../Models/CSliceGridData.h"


class CSliceGridItem : public CGridItem
{
    Q_OBJECT
public:
    CSliceGridItem(QWidget *parent = nullptr);
    ~CSliceGridItem();
public:
    void showProperty(QtTreePropertyBrowser *treeProperty);
protected:
    void onSelected(bool isSelected);
    void onState(const CGridItemData &data);
    void paintEvent(QPaintEvent *e);
protected slots:
    void propValueChanged(const QString &propName,const CSliceGridData &data);
private:
    CSliceGridProperty m_property;
    QPen m_pen;
    bool m_isSelected;
};

#endif // CSLICEGRIDITEM_H
