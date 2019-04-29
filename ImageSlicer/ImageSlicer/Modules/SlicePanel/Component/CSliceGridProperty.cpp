#include "CSliceGridProperty.h"

static const QString GROUP1_NAME = ("frame");
static const QString GROUP2_NAME = ("geometry");

static const QString KEY_ENABLE = ("enable");
static const QString KEY_NAME = ("name");
static const QString KEY_EXTRA = ("extra");
static const QString KEY_DESCRIPTION = ("description");

static const QString KEY_POS = ("pos");
static const QString KEY_SIZE = ("size");
static const QString KEY_CENTER = ("center");


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

    for(auto it : *m_pStringToProperty)
    {
        delete it;
    }

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

    item = m_pStringToProperty->value(KEY_ENABLE);
    item->setValue(m_data.enable);

    item = m_pStringToProperty->value(KEY_NAME);
    item->setValue(m_data.name);

    item = m_pStringToProperty->value(KEY_EXTRA);
    item->setValue(m_data.extra);

    item = m_pStringToProperty->value(KEY_DESCRIPTION);
    item->setValue(m_data.description);

    item = m_pStringToProperty->value(KEY_POS);
    item->setValue(m_data.pos);

    item = m_pStringToProperty->value(KEY_SIZE);
    item->setValue(m_data.size);

    item = m_pStringToProperty->value(KEY_CENTER);
    item->setValue(m_data.center);
}
////
void CSliceGridProperty::bindProperty(QtTreePropertyBrowser *treeProperty)
{
    treeProperty->clear();

    treeProperty->addProperty(m_pGroup1);
    treeProperty->addProperty(m_pGroup2);

    treeProperty->setFactoryForManager(m_pEditManager, m_pEditFactory);
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
    addProperty(m_pGroup1, m_pEditManager, QVariant::Bool, KEY_ENABLE, true);
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, KEY_NAME, "");
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, KEY_EXTRA, "");
    addProperty(m_pGroup1, m_pEditManager, QVariant::String, KEY_DESCRIPTION, "");

    addProperty(m_pGroup2, m_pEditManager, QVariant::Point, KEY_POS, QPoint(0,0));
    addProperty(m_pGroup2, m_pEditManager, QVariant::Size, KEY_SIZE, QSize(0,0));
    addProperty(m_pGroup2, m_pEditManager, QVariant::PointF, KEY_CENTER, QPointF(0.5,0.5));
}


void CSliceGridProperty::propValueChanged(QtProperty *property, const QVariant &value)
{
    //值绑定
    QtVariantProperty *item = nullptr;
    auto name = property->propertyName();
    item = m_pStringToProperty->value(name);

    if (name == KEY_NAME){
        m_data.name = value.toString();
    }else if (name == KEY_ENABLE){
        m_data.enable = value.toBool();
    }else if (name == KEY_EXTRA){
        m_data.extra = value.toString();
    }else if (name == KEY_DESCRIPTION){
        m_data.description = value.toString();
    }else if (name == KEY_POS){
        m_data.pos.setX(value.toPoint().x());
        m_data.pos.setY(value.toPoint().y());
    }else if (name == KEY_SIZE){
        m_data.size.setWidth(value.toSize().width());
        m_data.size.setHeight(value.toSize().height());
    }else if (name == KEY_CENTER){
        m_data.center.setX(value.toPoint().x());
        m_data.center.setY(value.toPoint().y());
    }

    emit dataChanged(name,m_data);
}
