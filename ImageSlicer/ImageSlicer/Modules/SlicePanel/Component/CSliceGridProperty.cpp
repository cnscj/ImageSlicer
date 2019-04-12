#include "CSliceGridProperty.h"

static const QString GROUP1_NAME = QStringLiteral("Group1");
static const QString GROUP2_NAME = QStringLiteral("Group2");

static const QString KEY_NAME = QStringLiteral("name");
static const QString KEY_ENABLE = QStringLiteral("enable");
static const QString KEY_REMARK = QStringLiteral("remark");
static const QString KEY_X = QStringLiteral("x");
static const QString KEY_Y = QStringLiteral("y");
static const QString KEY_WIDTH = QStringLiteral("width");
static const QString KEY_HEIGHT = QStringLiteral("height");


CSliceGridProperty::CSliceGridProperty()
{
    m_pEditManager = new QtVariantPropertyManager();
    m_pReadManager = new QtVariantPropertyManager();
    m_pEditFactory = new QtVariantEditorFactory();


    m_pPropertyToString = new QMap<QtVariantProperty *, QString>();
    m_pStringToProperty = new QMap<QString, QtVariantProperty *>();

    m_pGroup1 = m_pEditManager->addProperty(QtVariantPropertyManager::groupTypeId(), GROUP1_NAME);
    m_pGroup2 = m_pReadManager->addProperty(QtVariantPropertyManager::groupTypeId(), GROUP2_NAME);

    setupProperty();

    connect(m_pEditManager, &QtVariantPropertyManager::valueChanged, this, &CSliceGridProperty::propValueChanged);

}

CSliceGridProperty::~CSliceGridProperty()
{
    disconnect(m_pEditManager, &QtVariantPropertyManager::valueChanged, this, &CSliceGridProperty::propValueChanged);

    delete m_pGroup1;
    delete m_pGroup2;

    delete m_pPropertyToString;
    delete m_pStringToProperty;

    delete m_pEditManager;
    delete m_pReadManager;
    delete m_pEditFactory;
}
///
CSliceGridData &CSliceGridProperty::getData()
{
    return m_data;
}

void CSliceGridProperty::setData(const CSliceGridData &data)
{
    m_data = data;
    QtVariantProperty *item = nullptr;

    item = m_pStringToProperty->value(KEY_NAME);
    item->setValue(m_data.name);

    item = m_pStringToProperty->value(KEY_ENABLE);
    item->setValue(m_data.enable);

    item = m_pStringToProperty->value(KEY_REMARK);
    item->setValue(m_data.remark);

    item = m_pStringToProperty->value(KEY_X);
    item->setValue(m_data.pos.x());

    item = m_pStringToProperty->value(KEY_Y);
    item->setValue(m_data.pos.y());

    item = m_pStringToProperty->value(KEY_WIDTH);
    item->setValue(m_data.size.width());

    item = m_pStringToProperty->value(KEY_HEIGHT);
    item->setValue(m_data.size.height());

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
    m_pStringToProperty->insert(name,item);
    m_pPropertyToString->insert(item,name);

    return item;
}

void CSliceGridProperty::setupProperty()
{
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, KEY_NAME, "");
    addProperty(m_pGroup1, m_pEditManager, QVariant::Bool, KEY_ENABLE, true);
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, KEY_REMARK, "");

    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, KEY_X, 0);
    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, KEY_Y, 0);
    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, KEY_WIDTH, 0);
    addProperty(m_pGroup2, m_pEditManager, QVariant::Int, KEY_HEIGHT, 0);
}


void CSliceGridProperty::propValueChanged(QtProperty *property, const QVariant &value)
{
    //值绑定
    auto name = property->propertyName();

    if (name == KEY_NAME){
        m_data.name = value.toString();
    }else if (name == KEY_ENABLE){
        m_data.enable = value.toBool();
    }else if (name == KEY_REMARK){
        m_data.remark = value.toString();
    }else if (name == KEY_X){
        m_data.pos.setX(value.toInt());
    }else if (name == KEY_Y){
        m_data.pos.setY(value.toInt());
    }else if (name == KEY_WIDTH){
        m_data.size.setWidth(value.toInt());
    }else if (name == KEY_HEIGHT){
        m_data.size.setHeight(value.toInt());
    }

    emit dataChanged(name,m_data);
}
