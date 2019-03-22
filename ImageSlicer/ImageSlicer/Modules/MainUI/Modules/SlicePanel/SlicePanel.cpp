#include "SlicePanel.h"
#include "ui_SlicePanel.h"

CSlicePanel::CSlicePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicePanel)
{
    ui->setupUi(this);
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
