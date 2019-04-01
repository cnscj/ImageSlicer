#include "SlicePanel.h"
#include "ui_SlicePanel.h"
#include "ImageSlicer.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QtVariantPropertyManager>

#include "Modules/SliceEdit/SliceEdit.h"

static const double MAX_SCALE_VALUE = 16.0;  //最大缩放值
static const double MIN_SCALE_VALUE = 0.125;  //最小缩放值
static const double STEP_SCALE_VALUE = 1.125; //每次缩放值

CSlicePanel::CSlicePanel(QWidget *parent) :
    QWidget(parent),m_sliceMenu(this),
    ui(new Ui::CSlicePanel)
{
    ui->setupUi(this);

    QList<QAction*> actionList;
    actionList << ui->actionSlice;
    m_sliceMenu.addActions(actionList);//添加子项到主菜单

    ui->imageAttrList->setStyleSheet("background-color:transparent");

    connect(this,SIGNAL(imageDataUpdate()),this,SLOT(updateImgAttrList()));
    connect(ui->actionSlice,SIGNAL(triggered()),this,SLOT(editeSlice()));

    //TODO:属性表
    ui->propsWidget->clear();
    QtVariantPropertyManager *m_pVarManager;
    QtVariantEditorFactory *m_pVarFactory;
    m_pVarManager = new QtVariantPropertyManager();
    m_pVarFactory = new QtVariantEditorFactory();

    QtProperty *groupItem = m_pVarManager->addProperty(QtVariantPropertyManager::groupTypeId(),QStringLiteral("Group1"));

    QtVariantProperty *item = m_pVarManager->addProperty(QVariant::Int, QStringLiteral("Int: "));
    item->setValue(100);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::Bool,QStringLiteral("Bool: "));
    item->setValue(true);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::Double,QStringLiteral("Double: "));
    item->setValue(3.14);
    groupItem->addSubProperty(item);

    item = m_pVarManager->addProperty(QVariant::String,QStringLiteral("String: "));
    item->setValue(QStringLiteral("hello world"));
    groupItem->addSubProperty(item);

    ui->propsWidget->addProperty(groupItem);
    ui->propsWidget->setFactoryForManager(m_pVarManager,m_pVarFactory);
    connect(m_pVarManager, &QtVariantPropertyManager::valueChanged, this,[](QtProperty *property, const QVariant &value)
    {
        qDebug("%s",value.toString().toStdString().c_str());
    });
    /////////////////////
}

CSlicePanel::~CSlicePanel()
{
    delete ui;
}


bool CSlicePanel::loadImageFromFile(const QString &filePath)
{
    QImage temImg;
    bool ret = temImg.load(filePath);
    if (ret)
    {
        ui->imageWidget->setImage(temImg);
        m_imageFilePath = filePath;

        emit imageDataUpdate();
    }

    return ret;
}

void CSlicePanel::sliceImageBySize(const QSizeF &size)
{
    ui->gridArea->sliceGrids(nullptr,size);
    emit imageDataUpdate();
}

const QString &CSlicePanel::getImgOriPath() const
{
    return m_imageFilePath;
}

QSize CSlicePanel::getImageOriSize() const
{
    return ui->imageWidget->getOriSize();
}


void CSlicePanel::setPicBoxMode(CPictureBox::EZoomMode mode)
{
    ui->imageWidget->setMode(mode);
}

void CSlicePanel::keyPressEvent(QKeyEvent *e)
{
    //是否按住Alt键或Option键
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
       m_flagsMap[EActionMode::WantScale] = true;
       ui->scrollArea->setWheelScrollEnable(false);
    }
}
void CSlicePanel::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
       m_flagsMap[EActionMode::WantScale] = false;
       ui->scrollArea->setWheelScrollEnable(true);
    }
}

void CSlicePanel::wheelEvent(QWheelEvent *e)
{
    //如果按住了择标记为可缩放
    if (m_flagsMap[EActionMode::WantScale])
    {
        int numDegress = e->delta();
        double finalScale = ui->imageWidget->getScale();
        if (numDegress > 0)
        {
            finalScale = ((finalScale >= MAX_SCALE_VALUE) ? (MAX_SCALE_VALUE) : (finalScale * STEP_SCALE_VALUE));
        }
        else
        {
           finalScale = ((finalScale <= MIN_SCALE_VALUE) ? (MIN_SCALE_VALUE) : (finalScale / STEP_SCALE_VALUE));
        }
        ui->imageWidget->setScale(finalScale);
        emit imageDataUpdate();
    }
}

void CSlicePanel::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (e->buttons() & Qt::MiddleButton)
    {
        ui->imageWidget->setScale(1.0);
        emit imageDataUpdate();
    }
}

void CSlicePanel::contextMenuEvent(QContextMenuEvent *e)
{
    //TODO:菜单项应该单独写
    if (WidgetUtil::isCursorInWidget(ui->gridArea))
    {
        m_sliceMenu.exec(QCursor::pos());
    }
    else
    {
        QWidget::contextMenuEvent(e);
    }

}

void CSlicePanel::clearAttrList()
{
    int count = ui->imageAttrList->count();
    for(int index = 0; index < count; index++)
    {
        QListWidgetItem *item = ui->imageAttrList->takeItem(0);
        delete item;
    }
}

void CSlicePanel::setAttrListProvider(const QLinkedList<CImgAttrListItemData> &data)
{
    clearAttrList();

    int i = 0;
    foreach (auto it, data)
    {
        CImgAttrListItem *widget = new CImgAttrListItem();
        widget->setState(it,i);

        QListWidgetItem *item = new QListWidgetItem(ui->imageAttrList);
        ui->imageAttrList->addItem(item);
        item->setSizeHint(QSize(widget->size()));
        ui->imageAttrList->setItemWidget(item,widget);

        i++;
    }
}

void CSlicePanel::updateImgAttrList()
{
    QLinkedList<CImgAttrListItemData> data;

    QSize texOriSize = ui->imageWidget->getOriSize();
    QSize texCurSize = ui->imageWidget->getCurSize();
    double texScale = ui->imageWidget->getScale();
    int sliceCount = ui->gridArea->getSliceCount();

    data << CImgAttrListItemData("纹理尺寸",QString("(%1,%2)").arg(texOriSize.width()).arg(texOriSize.height()),"");
    data << CImgAttrListItemData("缩放尺寸",QString("(%1,%2)").arg(texCurSize.width()).arg(texCurSize.height()),"");
    data << CImgAttrListItemData("缩放倍率",QString("%1").arg(texScale),"");
    data << CImgAttrListItemData("总切片数",QString("%1").arg(sliceCount),"");

    setAttrListProvider(data);
}

void CSlicePanel::editeSlice()
{
    //TODO:打开编辑窗口
//    CSliceEdit::SShowParams params;

//    //填充结构体
//    params.filePath = slicePanel->getImgOriPath();
//    params.imgSize = slicePanel->getImageOriSize();
    qDebug("!!!!");
}
