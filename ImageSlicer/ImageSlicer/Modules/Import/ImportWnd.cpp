#include "ImportWnd.h"
#include "ui_ImportWnd.h"

CImportWnd::CImportWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CImportWnd)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width (),this->height ());
}

CImportWnd::~CImportWnd()
{
    delete ui;
}
