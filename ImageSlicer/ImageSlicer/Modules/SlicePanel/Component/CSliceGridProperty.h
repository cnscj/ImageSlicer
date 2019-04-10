#ifndef CSLICEGRIDPROPERTY_H
#define CSLICEGRIDPROPERTY_H
#include <QtTreePropertyBrowser>
#include <QtVariantPropertyManager>
#include "../Models/CSliceGridData.h"

class CSliceGridProperty : public QObject
{
    Q_OBJECT
public:
    CSliceGridProperty();
    ~CSliceGridProperty();
public:
    CSliceGridData &getData();
    void setData(const CSliceGridData &data);
public:
    void bindProperty(QtTreePropertyBrowser *treeProperty);
    void clearProperty();
protected:
    QtVariantProperty *addProperty(QtProperty *property,QtVariantPropertyManager *manager,int propertyType,QString name,QVariant defaultValue);
    void setupProperty();
signals:
    void dataChanged(const QString &propName,const CSliceGridData &data);
private slots:
    void propValueChanged(QtProperty *property, const QVariant &value);
private:
    QtVariantPropertyManager *m_pEditManager;
    QtVariantPropertyManager *m_pReadManager;
    QtVariantEditorFactory *m_pEditFactory;

    QMap<QtVariantProperty *, QString> *m_pPropertyToString;
    QMap<QString, QtVariantProperty *> *m_pStringToProperty;

    QtProperty *m_pGroup1;
    QtProperty *m_pGroup2;

    CSliceGridData m_data;
};

#endif // CSLICEGRIDPROPERTY_H
