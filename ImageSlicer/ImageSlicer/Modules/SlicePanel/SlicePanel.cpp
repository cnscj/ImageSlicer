#include "SlicePanel.h"
#include "ui_SlicePanel.h"
#include "ImageSlicer.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QtVariantPropertyManager>
#include "Component/UI/CGridArea.h"
#include "Component/CSliceGridItem.h"
#include "Component/Parser/CProjectDataParser.h"

static const QString KEY_TEXTURE_SIZE = ("纹理尺寸");
static const QString KEY_SCALE_SIZE = ("缩放尺寸");
static const QString KEY_SCALE_RATE = ("缩放倍率");
static const QString KEY_SLICE_COUNT = ("总切片数");

static const double MAX_SCALE_VALUE = 16.0;  //最大缩放值
static const double MIN_SCALE_VALUE = 0.125;  //最小缩放值
static const double STEP_SCALE_VALUE = 1.125; //每次缩放值

CSlicePanel::CSlicePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicePanel),m_isShowedGridsProperty(false)
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
    ui->gridArea->setItemCreator([=](const CGridItemData &)
    {
        auto item = new CSliceGridItem();
        item->setFileName(StringUtil::getFileName(this->getImgOriPath(),true));
        return item;
    });
    connect(ui->gridArea,&CGridArea::gridClicked,this,&CSlicePanel::sliceClicked);

    /////////////////////
    connect(this,&CSlicePanel::panelDataUpdate,this,&CSlicePanel::updateImgAttrList);
    connect(m_pSliceEditWnd,&CSliceEdit::sliceCallback,this,&CSlicePanel::editSliceCallback);
    connect(&m_gridsProperty,&CSliceGridsProperty::dataChanged,this,&CSlicePanel::propValueChanged);
}

CSlicePanel::~CSlicePanel()
{
    delete ui;
    delete m_pSliceMenu;
    delete m_pSliceEditWnd;
}
bool CSlicePanel::loadImageFromMemory(const QByteArray &data)
{
    QImage temImg;
    bool ret = temImg.loadFromData(data);
    if (ret)
    {
        ui->imageWidget->setImage(temImg);
        m_panelData.pPixmap = ui->imageWidget->getImage();
        m_panelData.imagePath = "";
        m_panelData.size = temImg.size();

        emit panelDataUpdate();
    }

    return ret;
}

bool CSlicePanel::loadImageFromFile(const QString &filePath)
{
    QImage temImg;
    bool ret = temImg.load(filePath);
    if (ret)
    {
        ui->imageWidget->setImage(temImg);
        m_panelData.pPixmap = ui->imageWidget->getImage();
        m_panelData.imagePath = filePath;
        m_panelData.size = temImg.size();

        emit panelDataUpdate();
    }

    return ret;
}
void CSlicePanel::setInitData(const SPanelInitParams &data)
{
    m_panelData.projectName = data.projectName;
    m_panelData.openPath = data.projectFile;

    if (data.projectType == EnumType::ESlicePanelType::Image)
    {
        if ( data.projectFile != "")
        {
            this->loadImageFromFile(data.projectFile);
        }
    }else if (data.projectType == EnumType::ESlicePanelType::Project)
    {
        if ( data.projectFile != "")
        {
            CProjectDataParser parser;
            CProjectDataParser::SInputParams params;
            params.widget = data.mainWnd;
            params.openPath = data.projectFile;

            parser.input(params);
        }
    }

    this->setPicBoxMode(CPictureBox::EZoomMode::AutoSize);//居中显示
}

const QString &CSlicePanel::getImgOriPath() const
{
    return m_panelData.imagePath;
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

void CSlicePanel::updateInfos()
{
    emit panelDataUpdate();
}

CSliceExportData CSlicePanel::getExportData()
{
    CSliceExportData data;
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

bool CSlicePanel::setImportData(CSliceImportData &data)
{
    //TODO:
    if (data.panelData.imagePath != "")
    {
        if (loadImageFromFile(data.panelData.imagePath))
        {
            for(auto it : data.gridsList)
            {
                auto data = it->getOriData();
                auto item = static_cast<CSliceGridItem *>(ui->gridArea->addGridItem(data));
                item->setPropertyData(it);
            }
            ui->gridArea->reset();
            ui->gridArea->resetIds();
            ui->gridArea->adjust();
            updateInfos();
        }
        return true;
    }
    else if (data.panelData.pPixmap)
    {
        //TODO:
        QByteArray dataArray;
        QDataStream in(&dataArray, QIODevice::ReadWrite);
        if (data.panelData.pPixmap)
        {
            in << *data.panelData.pPixmap;
            if (loadImageFromMemory(dataArray))
            {
                for(auto it : data.gridsList)
                {
                    auto data = it->getOriData();
                    auto item = static_cast<CSliceGridItem *>(ui->gridArea->addGridItem(data));
                    item->setPropertyData(it);
                }
                ui->gridArea->reset();
                ui->gridArea->resetIds();
                ui->gridArea->adjust();
                updateInfos();
            }
            return true;
        }

    }
    return false;
}

//
void CSlicePanel::keyPressEvent(QKeyEvent *e)
{
    //是否按住Alt键或Option键
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
       m_flagsMap[EActionMode::WantScale] = true;
       ui->scrollArea->setWheelScrollEnable(false);
    }
    else if(e->key() == Qt::Key_Comma || e->key() == Qt::Key_Control)
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
    }
    else if(e->key() == Qt::Key_Comma || e->key() == Qt::Key_Control)
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

    ui->gridArea->sliceGrids(ui->gridArea->getSelectList(),params.sliceSize);
    emit panelDataUpdate();
}

void CSlicePanel::editMergeGrids()
{
    ui->gridArea->mergeGrids(ui->gridArea->getSelectList());
    ui->actionMerge->setEnabled(false);
    ui->actionRemove->setEnabled(false);
    ui->propsWidget->clear();

    emit panelDataUpdate();
}

void CSlicePanel::editRemoveGrids()
{
    ui->gridArea->removeGrids(ui->gridArea->getSelectList());
    ui->actionMerge->setEnabled(false);
    ui->actionRemove->setEnabled(false);
    ui->propsWidget->clear();

    emit panelDataUpdate();
}

void CSlicePanel::sliceClicked(CGridItem *grid)
{
    auto item = static_cast<CSliceGridItem *>(grid);

    if (ui->gridArea->getSelectList().count() > 0)
    {
        if (ui->gridArea->getSelectList().count() == 1)
        {
            item->showProperty(ui->propsWidget);
            m_isShowedGridsProperty = false;
        }
        else
        {
            if (!m_isShowedGridsProperty)
            {
                CSliceGridsProperty::SShowParams params;
                params.name = item->getPropertyData()->name;
                params.enable = item->getPropertyData()->enable;

                m_gridsProperty.showProperty(ui->propsWidget,params);
                m_isShowedGridsProperty = true;
            }
        }
        ui->actionMerge->setEnabled(true);
        ui->actionRemove->setEnabled(true);
    }

    qDebug("点击:%d_%d",item->getData().pos.x(),item->getData().pos.y());
}

void CSlicePanel::propValueChanged(const QString &propName,const CSliceGridsData &data)
{
    auto list = ui->gridArea->getSelectList();
    int i = 1;
    for(auto it : list)
    {
        auto item = static_cast<CSliceGridItem *>(it);
        if (propName == "names")
        {
            item->getPropertyData()->name = QString("%1_%2").arg(data.names).arg(i,2,10,QLatin1Char('0'));
            item->setPropertyData(item->getPropertyData());

            i++;
        }
        else if(propName == "enables")
        {
            item->getPropertyData()->enable = data.enables;
            item->setPropertyData(item->getPropertyData());
        }
    }
}
