#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Modules/SlicePanle/SlicePanle.h"

const QString CMainWindow::s_tempTabName = "_Temp";

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

}

CMainWindow::~CMainWindow()
{
    delete ui;
}


void CMainWindow::addNewSlicePanel(const QString &title)
{
    auto tabWidget = ui->mainTabWidget;
    auto widget = new CSlicePanle(tabWidget);

    tabWidget->insertTab(0,widget,title);
}
