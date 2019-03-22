#include "ExportWnd.h"
#include "ui_ExportWnd.h"

CExportWnd::CExportWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CExportWnd)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width (),this->height ());
}

CExportWnd::~CExportWnd()
{
    delete ui;
}
