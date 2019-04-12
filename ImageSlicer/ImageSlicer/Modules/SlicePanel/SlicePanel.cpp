#include "SlicePanel.h"
#include "ui_SlicePanel.h"
#include "ImageSlicer.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QtVariantPropertyManager>
#include "Component/UI/CGridArea.h"
#include "Component/CSliceGridItem.h"

static const QString KEY_TEXTURE_SIZE = QStringLiteral("纹理尺寸");
static const QString KEY_SCALE_SIZE = QStringLiteral("缩放尺寸");
static const QString KEY_SCALE_RATE = QStringLiteral("缩放倍率");
static const QString KEY_SLICE_COUNT = QStringLiteral("总切片数");

static const double MAX_SCALE_VALUE = 16.0;  //最大缩放值
static const double MIN_SCALE_VALUE = 0.125;  //最小缩放值
static const double STEP_SCALE_VALUE = 1.125; //每次缩放值

CSlicePanel::CSlicePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicePanel)
{
    ui->setupUi(this);
    ui->gridArea->setSelectMode(CGridArea::ESelectMode::Single);

    //右键菜单
    m_pSliceMenu = new QMenu(this);
    QList<QAction*> actionList;
    actionList << ui->actionSlice;
    actionList << ui->actionMerge;
    actionList << ui->actionRemove;
    ui->actionMerge->setEnabled(false);
    ui->actionRemove->setEnabled(false);
    m_pSliceMenu->addActions(actionList);//添加子项到主菜单
    connect(ui->actionSlice,SIGNAL(triggered()),this,SLOT(editSliceWnd()));
    connect(ui->actionMerge,SIGNAL(triggered()),this,SLOT(editMergeGrids()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(editRemoveGrids()));

    //划分切片窗口
    m_pSliceEditWnd = new CSliceEdit();
    m_pSliceEditWnd->setAttribute(Qt::WA_ShowModal, true);   //改为模态窗口

    //切片构造函数
    ui->gridArea->setItemCreator([=](const CGridItemData &data)
    {
        auto item = new CSliceGridItem();
        item->setFileName(StringUtil::getFileName(this->getImgOriPath(),true));
        return item;
    });
    connect(ui->gridArea,&CGridArea::gridClicked,this,&CSlicePanel::sliceClicked);

    /////////////////////
    connect(this,&CSlicePanel::panelDataUpdate,this,&CSlicePanel::updateImgAttrList);
    connect(m_pSliceEditWnd,&CSliceEdit::sliceCallback,this,&CSlicePanel::editSliceCallback);

}

CSlicePanel::~CSlicePanel()
{
    delete ui;
    delete m_pSliceMenu;
    delete m_pSliceEditWnd;
}


bool CSlicePanel::loadImageFromFile(const QString &filePath)
{
    QImage temImg;
    bool ret = temImg.load(filePath);
    if (ret)
    {
        ui->imageWidget->setImage(temImg);
        m_panelData.filePath = filePath;
        m_panelData.size = temImg.size();

        emit panelDataUpdate();
    }

    return ret;
}


const QString &CSlicePanel::getImgOriPath() const
{
    return m_panelData.filePath;
}

QSize CSlicePanel::getImageOriSize() const
{
    return m_panelData.size;
}


void CSlicePanel::setPicBoxMode(CPictureBox::EZoomMode mode)
{
    ui->imageWidget->setMode(mode);
}
const CSlicePanelData &CSlicePanel::getPanelData()
{
    return m_panelData;
}

CSliceResultData CSlicePanel::getResultData()
{
    CSliceResultData data;
    data.panelData = &m_panelData;

    auto pItemList = ui->gridArea->getGirds();
    QList<CSliceGridData *> gridsList;
    for(auto it : *pItemList)
    {
        auto item = static_cast<CSliceGridItem *>(it);
        gridsList.push_back(item->getPropertyData());
    }
    data.gridsList = gridsList;

    return data;
}
//
void CSlicePanel::keyPressEvent(QKeyEvent *e)
{
    //是否按住Alt键或Option键
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
       m_flagsMap[EActionMode::WantScale] = true;
       ui->scrollArea->setWheelScrollEnable(false);
    }else if(e->key() == Qt::Key_Comma || e->key() == Qt::Key_Control)
    {
        ui->gridArea->setSelectMode(CGridArea::ESelectMode::Multiple);
    }
}
void CSlicePanel::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
       m_flagsMap[EActionMode::WantScale] = false;
       ui->scrollArea->setWheelScrollEnable(true);
    }else if(e->key() == Qt::Key_Comma || e->key() == Qt::Key_Control)
    {
        ui->gridArea->setSelectMode(CGridArea::ESelectMode::Single);
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
        ui->scrollArea->update();
        emit panelDataUpdate();
    }
}

void CSlicePanel::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (e->buttons() & Qt::MiddleButton)
    {
        ui->imageWidget->setScale(1.0);
        ui->scrollArea->update();
        emit panelDataUpdate();
    }
}

void CSlicePanel::contextMenuEvent(QContextMenuEvent *e)
{
    //滚动到最左侧时,最右侧非窗口区能够被点到
    if (WidgetUtil::isCursorInWidget(ui->scrollArea))
    {
        if (WidgetUtil::isCursorInWidget(ui->gridArea))
        {
            m_pSliceMenu->exec(QCursor::pos());
        }
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

    data << CImgAttrListItemData(KEY_TEXTURE_SIZE, QString("%1,%2").arg(texOriSize.width()).arg(texOriSize.height()), "");
    data << CImgAttrListItemData(KEY_SCALE_SIZE, QString("%1,%2").arg(texCurSize.width()).arg(texCurSize.height()), "");
    data << CImgAttrListItemData(KEY_SCALE_RATE, QString("%1").arg(texScale), "");
    data << CImgAttrListItemData(KEY_SLICE_COUNT, QString("%1").arg(sliceCount), "");

    setAttrListProvider(data);
}

void CSlicePanel::editSliceWnd()
{
    CSliceEdit::SShowParams params;
    auto slicePanel = static_cast<CSlicePanel *>(this);
    //填充结构体

    if (ui->gridArea->getSelectList().count() > 0)
    {
        auto item = ui->gridArea->getSelectList().at(0);
        params.imgSize = item->getData().size;
    }else
    {
        params.filePath = slicePanel->getImgOriPath();
        params.imgSize = slicePanel->getImageOriSize();
    }

    m_pSliceEditWnd->showWithParams(params);
}
void CSlicePanel::editSliceCallback(const CSliceEdit::SSliceCallbackParams &params)
{
    qDebug("回调:%f,%f",params.sliceSize.width(),params.sliceSize.height());

    if (ui->gridArea->getSelectList().count() > 0)
    {
        auto item = ui->gridArea->getSelectList().at(0);
        ui->gridArea->sliceGrids(item,params.sliceSize);
    }
    else
    {
        ui->gridArea->sliceGrids(nullptr,params.sliceSize);
    }

    emit panelDataUpdate();
}
void CSlicePanel::editMergeGrids()
{
    ui->gridArea->mergeGrids(ui->gridArea->getSelectList());
    emit panelDataUpdate();
}
void CSlicePanel::editRemoveGrids()
{
    ui->gridArea->removeGrids(ui->gridArea->getSelectList());
    emit panelDataUpdate();
}
void CSlicePanel::sliceClicked(CGridItem *grid)
{
    auto item = static_cast<CSliceGridItem *>(grid);
    item->showProperty(ui->propsWidget);
    if (ui->gridArea->getSelectList().count() > 0)
    {
        ui->actionMerge->setEnabled(true);
        ui->actionRemove->setEnabled(true);
    }else
    {
        ui->actionMerge->setEnabled(false);
        ui->actionRemove->setEnabled(false);
    }

    qDebug("点击:%d_%d",item->getData().pos.x(),item->getData().pos.y());
}
