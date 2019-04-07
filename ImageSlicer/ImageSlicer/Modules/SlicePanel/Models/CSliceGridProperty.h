#ifndef CSLICEGRIDPROPERTY_H
#define CSLICEGRIDPROPERTY_H
#include <QtTreePropertyBrowser>
#include <QtVariantPropertyManager>
#include "CSliceGridData.h"

class CSliceGridProperty : public QObject
{
    Q_OBJECT
public:
    CSliceGridProperty();
    ~CSliceGridProperty();
public:
    void bindProperty(QtTreePropertyBrowser *treeProperty);
protected:
    QtVariantProperty *addProperty(QtProperty *property,QtVariantPropertyManager *manager,int propertyType,QString name,QVariant defaultValue);
    void setupProperty(CSliceGridData *data);
    void clearProperty();
private slots:
    void propValueChanged(QtProperty *property, const QVariant &value);
private:
    QtVariantPropertyManager *m_pEditManager;
    QtVariantPropertyManager *m_pReadManager;
    QtVariantEditorFactory *m_pEditFactory;

    QMap<QtProperty *, void *> *m_pPropertyToBindValue;

    QtProperty *m_pGroup1;
    QtProperty *m_pGroup2;

    CSliceGridData *m_pData;
};

#endif // CSLICEGRIDPROPERTY_H
