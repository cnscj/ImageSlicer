#include "SlicePanel.h"
#include "ui_SlicePanel.h"
#include <QKeyEvent>
#include <QWheelEvent>

CSlicePanel::CSlicePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicePanel)
{
    ui->setupUi(this);

    ui->imageAttrList->setStyleSheet("background-color:transparent");
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
    }

    return ret;
}

const QString &CSlicePanel::getCurImgPath()
{
    return m_imageFilePath;
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
       m_flagsMap["isWantToScale"] = true;
    }
}
void CSlicePanel::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Option || e->key() == Qt::Key_Alt)
    {
       m_flagsMap["isWantToScale"] = false;
    }
}

void CSlicePanel::wheelEvent(QWheelEvent *e)
{
    //如果按住了择标记为可缩放
    if ( m_flagsMap["isWantToScale"] )
    {
        int numDegress = e->delta();
        double finalScale = ui->imageWidget->getScale();
        if (numDegress > 0)
        {
            finalScale = ((finalScale >= 15.0) ? (15.0) : (finalScale * 1.15));
        }
        else
        {
           finalScale = ((finalScale <= 0.05) ? (0.05) : (finalScale / 1.15));
        }
        qDebug("%f",finalScale);
        ui->imageWidget->setScale(finalScale);

        //TODO:沒有及时重绘,锚点位置不对图片并没有居中,窗体大小也没有及时改变

    }
}

void CSlicePanel::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    ui->imageWidget->setScale(1.0);
}
