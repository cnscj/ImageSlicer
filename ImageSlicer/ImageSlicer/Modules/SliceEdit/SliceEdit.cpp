#include "SliceEdit.h"
#include "ui_SliceEdit.h"

CSliceEdit::CSliceEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSliceEdit)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    connect(ui->col_grid_rb,SIGNAL(toggled(bool)),ui->col_grid_le,SLOT(setEnabled(bool)));
    connect(ui->col_pixel_rb,SIGNAL(toggled(bool)),ui->col_pixel_le,SLOT(setEnabled(bool)));
    connect(ui->row_grid_rb,SIGNAL(toggled(bool)),ui->row_grid_le,SLOT(setEnabled(bool)));
    connect(ui->row_pixel_rb,SIGNAL(toggled(bool)),ui->row_pixel_le,SLOT(setEnabled(bool)));

    connect(ui->col_grid_rb,SIGNAL(toggled(bool)),ui->col_grid_le,SLOT(setFocus()));
    connect(ui->col_pixel_rb,SIGNAL(toggled(bool)),ui->col_pixel_le,SLOT(setFocus()));
    connect(ui->row_grid_rb,SIGNAL(toggled(bool)),ui->row_grid_le,SLOT(setFocus()));
    connect(ui->row_pixel_rb,SIGNAL(toggled(bool)),ui->row_pixel_le,SLOT(setFocus()));

    connect(ui->cancel_pb,SIGNAL(released()),this,SLOT(hide()));
}

CSliceEdit::~CSliceEdit()
{
    delete ui;
}
