#include "CSliceGridProperty.h"

CSliceGridProperty::CSliceGridProperty()
{
    m_pEditManager = new QtVariantPropertyManager();
    m_pReadManager = new QtVariantPropertyManager();
    m_pEditFactory = new QtVariantEditorFactory();

    m_pPropertyToBindValue = new QMap<QtProperty *, void *>();

    m_pGroup1 = m_pEditManager->addProperty(QtVariantPropertyManager::groupTypeId(), QStringLiteral("Group1"));
    m_pGroup2 = m_pReadManager->addProperty(QtVariantPropertyManager::groupTypeId(), QStringLiteral("Group2"));

    connect(m_pEditManager, &QtVariantPropertyManager::valueChanged, this, &CSliceGridProperty::propValueChanged);

}

CSliceGridProperty::~CSliceGridProperty()
{
    disconnect(m_pEditManager, &QtVariantPropertyManager::valueChanged, this, &CSliceGridProperty::propValueChanged);

    delete m_pGroup1;
    delete m_pGroup2;

    delete m_pPropertyToBindValue;

    delete m_pEditManager;
    delete m_pReadManager;
    delete m_pEditFactory;
}
////
void CSliceGridProperty::bindProperty(QtTreePropertyBrowser *treeProperty)
{
    treeProperty->clear();

    treeProperty->addProperty(m_pGroup1);
    treeProperty->addProperty(m_pGroup2);

    treeProperty->setFactoryForManager(m_pEditManager,m_pEditFactory);
}

////
QtVariantProperty *CSliceGridProperty::addProperty(QtProperty *property, QtVariantPropertyManager *manager,int propertyType,QString name,QVariant defaultValue)
{
    QtVariantProperty *item = nullptr;
    item = manager->addProperty(propertyType, name);
    item->setValue(defaultValue);
    property->addSubProperty(item);

    return item;
}

void CSliceGridProperty::setupProperty(CSliceGridData *data)
{

    //TODO:
    m_pData = data;
//    QtVariantProperty *item = nullptr;

    addProperty(m_pGroup1, m_pEditManager, QVariant::String, QStringLiteral("name"), data->name);
    addProperty(m_pGroup1, m_pEditManager, QVariant::Bool, QStringLiteral("enabled"), data->enable);
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, QStringLiteral("remark"), data->remark);

    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, QStringLiteral("x"), data->pos.x());
    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, QStringLiteral("y"), data->pos.y());
    addProperty(m_pGroup2, m_pEditManager, QVariant::Int ,QStringLiteral("width"), data->size.width());
    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, QStringLiteral("height"), data->size.height());
}


void CSliceGridProperty::propValueChanged(QtProperty *property, const QVariant &value)
{
    qDebug("%s:%s",property->propertyName().toStdString().c_str(),value.toString().toStdString().c_str());
}
