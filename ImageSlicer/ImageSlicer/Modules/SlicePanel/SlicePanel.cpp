#include "SlicePanel.h"
#include "ui_SlicePanel.h"
#include <QKeyEvent>
#include <QWheelEvent>

static const double MAX_SCALE_VALUE = 16.0;  //最大缩放值
static const double MIN_SCALE_VALUE = 0.125;  //最小缩放值
static const double STEP_SCALE_VALUE = 1.125; //每次缩放值

CSlicePanel::CSlicePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicePanel)
{
    ui->setupUi(this);

    ui->imageAttrList->setStyleSheet("background-color:transparent");

    connect(this,SIGNAL(imageDataUpdate()),this,SLOT(updateImgAttrList()));
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

void CSlicePanel::sliceImageBySize(const QSize &size)
{
    ui->gridArea->sliceGrids(size);
    emit imageDataUpdate();
}

const QString &CSlicePanel::getCurImgPath() const
{
    return m_imageFilePath;
}

const QSize &CSlicePanel::getCurImageSize() const
{
    return ui->imageWidget->getPixmapSize();
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
    if ( m_flagsMap[EActionMode::WantScale] )
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
    }
}

void CSlicePanel::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (e->buttons() & Qt::MiddleButton)
    {
        ui->imageWidget->setScale(1.0);
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
    //TODO:
    QLinkedList<CImgAttrListItemData> data;
    data << CImgAttrListItemData("纹理尺寸",QString("(%1,%2)").arg(0).arg(0),"");
    data << CImgAttrListItemData("切片尺寸",QString("(%1,%2)").arg(0).arg(0),"");
    data << CImgAttrListItemData("切片总数",QString("%1").arg(0),"");
    data << CImgAttrListItemData("缩放尺寸",QString("(%2,%3)").arg(120).arg(120),"");
    data << CImgAttrListItemData("缩放倍率",QString("%1").arg(1.2),"");

    setAttrListProvider(data);
}
