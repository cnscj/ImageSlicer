#include "SliceEdit.h"
#include "ui_SliceEdit.h"

//TODO:最大切片数,像素不应该超过图片尺寸

CSliceEdit::CSliceEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSliceEdit)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width (),this->height ());

    connect(ui->col_grid_rb,SIGNAL(toggled(bool)),ui->col_grid_le,SLOT(setEnabled(bool)));
    connect(ui->col_pixel_rb,SIGNAL(toggled(bool)),ui->col_pixel_le,SLOT(setEnabled(bool)));
    connect(ui->row_grid_rb,SIGNAL(toggled(bool)),ui->row_grid_le,SLOT(setEnabled(bool)));
    connect(ui->row_pixel_rb,SIGNAL(toggled(bool)),ui->row_pixel_le,SLOT(setEnabled(bool)));

    connect(ui->col_grid_rb,SIGNAL(toggled(bool)),ui->col_grid_le,SLOT(setFocus()));
    connect(ui->col_pixel_rb,SIGNAL(toggled(bool)),ui->col_pixel_le,SLOT(setFocus()));
    connect(ui->row_grid_rb,SIGNAL(toggled(bool)),ui->row_grid_le,SLOT(setFocus()));
    connect(ui->row_pixel_rb,SIGNAL(toggled(bool)),ui->row_pixel_le,SLOT(setFocus()));

    connect(ui->ok_pb,SIGNAL(released()),this,SLOT(sliceHandle()));
    connect(ui->cancel_pb,SIGNAL(released()),this,SLOT(hide()));

}

CSliceEdit::~CSliceEdit()
{
    delete ui;
}

void CSliceEdit::showWithParams(SShowParams &params)
{
    qDebug("窗口参数:%s",params.filePath.toStdString().c_str());
    m_showParams = params;
    QWidget::show();
}

void CSliceEdit::sliceHandle()
{
    SSliceCallbackParams params;
    params.test = "TEST";
    emit sliceCallback(params);
    hide();
}
