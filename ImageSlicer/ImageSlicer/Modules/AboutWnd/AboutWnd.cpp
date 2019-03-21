#include "AboutWnd.h"
#include "ui_AboutWnd.h"

CAboutWnd::CAboutWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAboutWnd)
{
    ui->setupUi(this);
}

CAboutWnd::~CAboutWnd()
{
    delete ui;
}
