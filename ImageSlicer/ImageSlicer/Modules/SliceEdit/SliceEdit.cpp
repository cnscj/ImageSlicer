#include "SliceEdit.h"
#include "ui_SliceEdit.h"
#include <QIntValidator>
//TODO:最大切片数,像素不应该超过图片尺寸

CSliceEdit::CSliceEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSliceEdit)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width (),this->height ());

    ui->col_grid_le->setValidator(new QIntValidator(1, 999999, this));
    ui->col_pixel_le->setValidator(new QIntValidator(1, 999999, this));
    ui->row_grid_le->setValidator(new QIntValidator(1, 999999, this));
    ui->row_pixel_le->setValidator(new QIntValidator(1, 999999, this));

    connect(ui->col_grid_rb,SIGNAL(toggled(bool)),ui->col_grid_le,SLOT(setEnabled(bool)));
    connect(ui->col_pixel_rb,SIGNAL(toggled(bool)),ui->col_pixel_le,SLOT(setEnabled(bool)));
    connect(ui->row_grid_rb,SIGNAL(toggled(bool)),ui->row_grid_le,SLOT(setEnabled(bool)));
    connect(ui->row_pixel_rb,SIGNAL(toggled(bool)),ui->row_pixel_le,SLOT(setEnabled(bool)));

    connect(ui->col_grid_rb,SIGNAL(toggled(bool)),ui->col_grid_le,SLOT(setFocus()));
    connect(ui->col_pixel_rb,SIGNAL(toggled(bool)),ui->col_pixel_le,SLOT(setFocus()));
    connect(ui->row_grid_rb,SIGNAL(toggled(bool)),ui->row_grid_le,SLOT(setFocus()));
    connect(ui->row_pixel_rb,SIGNAL(toggled(bool)),ui->row_pixel_le,SLOT(setFocus()));

    connect(ui->col_grid_le,&QLineEdit::textEdited,this,&CSliceEdit::ColGridEdited);
    connect(ui->col_pixel_le,&QLineEdit::textEdited,this,&CSliceEdit::ColPixelEdited);
    connect(ui->row_grid_le,&QLineEdit::textEdited,this,&CSliceEdit::RowGridEdited);
    connect(ui->row_pixel_le,&QLineEdit::textEdited,this,&CSliceEdit::RowPixelEdited);

    connect(ui->ok_pb,SIGNAL(released()),this,SLOT(sliceHandle()));
    connect(ui->cancel_pb,SIGNAL(released()),this,SLOT(hide()));

}

CSliceEdit::~CSliceEdit()
{
    delete ui;
}

void CSliceEdit::showWithParams(SShowParams &params)
{
    qDebug("窗口参数:(%d,%d)",params.imgSize.width(),params.imgSize.height());
    m_showParams = params;

    ui->col_pixel_le->setText(QString("%1").arg(params.imgSize.height()));
    ui->row_pixel_le->setText(QString("%1").arg(params.imgSize.width()));
    ui->col_grid_le->setText(QString("%1").arg(1));
    ui->row_grid_le->setText(QString("%1").arg(1));

    QWidget::show();
}

void CSliceEdit::sliceHandle()
{
    SSliceCallbackParams params;

    QString colGridText = ui->col_grid_le->text();
    QString colPixelText = ui->col_pixel_le->text();
    QString rowGridText = ui->row_grid_le->text();
    QString rowPixelText = ui->row_pixel_le->text();

    double finalFrameWidth = colPixelText.toInt();
    double finalFrameHeight = rowPixelText.toInt();

    if (ui->col_grid_rb->isChecked())
    {
        finalFrameHeight = m_showParams.imgSize.height()/colGridText.toInt();
        params.horizon = QPair<ESliceType,int>(ESliceType::Part,colGridText.toInt());
    }
    else if (ui->col_pixel_rb->isChecked())
    {
        params.horizon = QPair<ESliceType,int>(ESliceType::Size,colPixelText.toInt());
    }

    if (ui->row_grid_rb->isChecked())
    {
        finalFrameWidth = m_showParams.imgSize.width()/rowGridText.toInt();
        params.vertical = QPair<ESliceType,int>(ESliceType::Part,rowGridText.toInt());
    }
    else if (ui->row_pixel_rb->isChecked())
    {
        params.vertical = QPair<ESliceType,int>(ESliceType::Size,rowPixelText.toInt());
    }

    params.sliceSize = QSizeF(finalFrameWidth,finalFrameHeight);
    emit sliceCallback(params);
    hide();
}

void CSliceEdit::showResultText()
{
    QString colGridText = ui->col_grid_le->text();
    QString colPixelText = ui->col_pixel_le->text();
    QString rowGridText = ui->row_grid_le->text();
    QString rowPixelText = ui->row_pixel_le->text();

    double finalFrameWidth = colPixelText.toInt();
    double finalFrameHeight = rowPixelText.toInt();

    if (ui->col_grid_rb->isChecked())
    {
        finalFrameHeight = m_showParams.imgSize.height()/colGridText.toInt();
    }
    if (ui->row_grid_rb->isChecked())
    {
        finalFrameWidth = m_showParams.imgSize.width()/rowGridText.toInt();
    }

    QString retText = QString("(%1,%2)").arg((int)finalFrameWidth).arg((int)finalFrameHeight);

    ui->size_lb->setText(retText);
}

void CSliceEdit::ColGridEdited(const QString &str)
{
    QString retStr = str;
    retStr = (retStr.toInt() <= 0) ? QString("%1").arg(1) : retStr;
    retStr = (retStr.toInt() >= m_showParams.imgSize.height()) ? QString("%1").arg(m_showParams.imgSize.height()) : retStr;
    ui->col_grid_le->setText(retStr);
    ui->col_pixel_le->setText(QString("%1").arg(m_showParams.imgSize.height()/retStr.toInt()));
}
void CSliceEdit::ColPixelEdited(const QString &str)
{
    QString retStr = str;
    retStr = (retStr.toInt() <= 0) ? QString("%1").arg(1) : retStr;
    retStr = (retStr.toInt() >= m_showParams.imgSize.height()) ? QString("%1").arg(m_showParams.imgSize.height()) : retStr;
    ui->col_pixel_le->setText(retStr);
    ui->col_grid_le->setText(QString("%1").arg(m_showParams.imgSize.height()/retStr.toInt()));
}
void CSliceEdit::RowGridEdited(const QString &str)
{
    QString retStr = str;
    retStr = (retStr.toInt() <= 0) ? QString("%1").arg(1) : retStr;
    retStr = (retStr.toInt() >= m_showParams.imgSize.width()) ? QString("%1").arg(m_showParams.imgSize.width()) : retStr;
    ui->row_grid_le->setText(retStr);
    ui->row_pixel_le->setText(QString("%1").arg(m_showParams.imgSize.width()/retStr.toInt()));
}
void CSliceEdit::RowPixelEdited(const QString &str)
{
    QString retStr = str;
    retStr = (retStr.toInt() <= 0) ? QString("%1").arg(1) : retStr;
    retStr = (retStr.toInt() >= m_showParams.imgSize.width()) ? QString("%1").arg(m_showParams.imgSize.width()) : retStr;
    ui->row_pixel_le->setText(retStr);
    ui->row_grid_le->setText(QString("%1").arg(m_showParams.imgSize.width()/retStr.toInt()));
}
