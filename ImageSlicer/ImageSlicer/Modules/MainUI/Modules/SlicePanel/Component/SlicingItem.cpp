#include "SlicingItem.h"
#include "ui_SlicingItem.h"

CSlicingItem::CSlicingItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSlicingItem)
{
    ui->setupUi(this);
}

CSlicingItem::~CSlicingItem()
{
    delete ui;
}


