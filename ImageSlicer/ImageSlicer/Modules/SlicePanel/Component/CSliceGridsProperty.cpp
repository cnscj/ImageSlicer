#include "CSliceGridsProperty.h"

static const QString GROUP1_NAME = ("attrs");

static const QString KEY_NAMES = ("names");
static const QString KEY_ENABLES = ("enables");

CSliceGridsProperty::CSliceGridsProperty():m_isShowSetOk(false)
{
    m_pEditManager = new QtVariantPropertyManager();
    m_pReadManager = new QtVariantPropertyManager();
    m_pEditFactory = new QtVariantEditorFactory();

    m_pPropertyToString = new QMap<QtVariantProperty *, QString>();
    m_pStringToProperty = new QMap<QString, QtVariantProperty *>();

    m_pGroup1 = m_pEditManager->addProperty(QtVariantPropertyManager::groupTypeId(), GROUP1_NAME);
    setupProperty();

    connect(m_pEditManager, &QtVariantPropertyManager::valueChanged, this, &CSliceGridsProperty::propValueChanged);
}

CSliceGridsProperty::~CSliceGridsProperty()
{
    disconnect(m_pEditManager, &QtVariantPropertyManager::valueChanged, this, &CSliceGridsProperty::propValueChanged);

    delete m_pGroup1;

    delete m_pPropertyToString;
    delete m_pStringToProperty;

    delete m_pEditManager;
    delete m_pReadManager;
    delete m_pEditFactory;
}
///
CSliceGridsData &CSliceGridsProperty::getData()
{
    return m_data;
}

void CSliceGridsProperty::setData(const CSliceGridsData &data)
{
    m_data = data;
    QtVariantProperty *item = nullptr;

    item = m_pStringToProperty->value(KEY_NAMES);
    item->setValue(m_data.names);

    item = m_pStringToProperty->value(KEY_ENABLES);
    item->setValue(m_data.enables);
}
////
void CSliceGridsProperty::showProperty(QtTreePropertyBrowser *treeProperty,SShowParams &params)
{
    m_data.names = params.name;
    m_data.enables = params.enable;


    m_isShowSetOk = false;
    setData(m_data);
    m_isShowSetOk = true;
    ///
    treeProperty->clear();

    for(auto it : m_pGroup1->subProperties())
    {
        treeProperty->addProperty(it);
    }

    treeProperty->setFactoryForManager(m_pEditManager,m_pEditFactory);
}

////
QtVariantProperty *CSliceGridsProperty::addProperty(QtProperty *property, QtVariantPropertyManager *manager,int propertyType,QString name,QVariant defaultValue)
{
    QtVariantProperty *item = nullptr;
    item = manager->addProperty(propertyType, name);
    item->setValue(defaultValue);
    property->addSubProperty(item);
    m_pStringToProperty->insert(name,item);
    m_pPropertyToString->insert(item,name);

    return item;
}

void CSliceGridsProperty::setupProperty()
{
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, KEY_NAMES, "");
    addProperty(m_pGroup1, m_pEditManager, QVariant::Bool, KEY_ENABLES, "");
}
void CSliceGridsProperty::propValueChanged(QtProperty *property, const QVariant &value)
{
    if (!m_isShowSetOk) return ;

    //值绑定
    auto name = property->propertyName();

    if (name == KEY_NAMES)
    {
        m_data.names = value.toString();
    }
    else if(name == KEY_ENABLES)
    {
        m_data.enables = value.toBool();
    }
    emit dataChanged(name,m_data);
}

