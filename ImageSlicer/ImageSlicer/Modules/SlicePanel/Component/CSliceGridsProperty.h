#ifndef CSLICEGRIDSPROPERTY_H
#define CSLICEGRIDSPROPERTY_H

#include <QtTreePropertyBrowser>
#include <QtVariantPropertyManager>
#include "../Models/CSliceGridsData.h"
class CSliceGridsProperty : public QObject
{
    Q_OBJECT
public:
    struct SShowParams
    {
        QString name;
        bool enable;
    };
public:
    CSliceGridsProperty();
    ~CSliceGridsProperty();
public:
    CSliceGridsData &getData();
    void setData(const CSliceGridsData &data);
public:
    void showProperty(QtTreePropertyBrowser *treeProperty,SShowParams &params);
    void clearProperty();
protected:
    QtVariantProperty *addProperty(QtProperty *property,QtVariantPropertyManager *manager,int propertyType,QString name,QVariant defaultValue);
    void setupProperty();
signals:
    void dataChanged(const QString &propName,const CSliceGridsData &data);
private slots:
    void propValueChanged(QtProperty *property, const QVariant &value);
private:
    QtVariantPropertyManager *m_pEditManager;
    QtVariantPropertyManager *m_pReadManager;
    QtVariantEditorFactory *m_pEditFactory;

    QMap<QtVariantProperty *, QString> *m_pPropertyToString;
    QMap<QString, QtVariantProperty *> *m_pStringToProperty;

    QtProperty *m_pGroup1;

    CSliceGridsData m_data;
    bool m_isShowSetOk;
};

#endif // CSLICEGRIDSPROPERTY_H
