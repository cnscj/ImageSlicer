#include "AboutWnd.h"
#include "ui_AboutWnd.h"

CAboutWnd::CAboutWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAboutWnd)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(),this->height());
    connect(ui->pushButton,&QPushButton::click,this,&CAboutWnd::clickOk);
}

CAboutWnd::~CAboutWnd()
{
    delete ui;
}
void CAboutWnd::clickOk()
{
    hide();
}
