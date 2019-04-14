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
    CSliceGridData *getPropertyData();
    void setPropertyData(CSliceGridData *data);

    void setFileName(const QString &name);
    const QString &getFileName();
protected:
    void onState(const CGridItemData &data);
    void onSelected(bool isSelected);
    void onIndex(int index);

    void paintEvent(QPaintEvent *e);
protected slots:
    void propValueChanged(const QString &propName,const CSliceGridData &data);
private:
    QString m_fileName;
    CSliceGridProperty m_property;
    QPen m_pen;
    bool m_isSelected;
};

#endif // CSLICEGRIDITEM_H
