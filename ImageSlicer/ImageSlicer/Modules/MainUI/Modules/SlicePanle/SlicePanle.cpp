#include "SlicePanle.h"
#include "ui_SlicePanle.h"

CSlicePanle::CSlicePanle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicePanle)
{
    ui->setupUi(this);
}

CSlicePanle::~CSlicePanle()
{
    delete ui;
}
