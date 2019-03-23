#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ImageSlicer.h"
#include "Modules/SlicePanel/SlicePanel.h"
#include "Modules/SliceEdit/SliceEdit.h"
#include "Modules/Export/ExportWnd.h"
#include "Modules/Import/ImportWnd.h"
#include "Modules/AboutWnd/AboutWnd.h"

#include "Modules/SlicePanel/Models/CSliceGridData.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    m_sliceEditWnd = new CSliceEdit();
    m_sliceEditWnd->setAttribute(Qt::WA_ShowModal, true);   //改为模态窗口

    m_exportWnd = new CExportWnd();
    m_exportWnd->setAttribute(Qt::WA_ShowModal, true);   //改为模态窗口

    m_importWnd = new CImportWnd();
    m_importWnd->setAttribute(Qt::WA_ShowModal, true);   //改为模态窗口

    ///////
    this->setAcceptDrops(true);//设置窗口启用拖动
    ui->actionEditSlice->setEnabled(false);

    connect(ui->actionEditSlice,SIGNAL(triggered()),this,SLOT(openSliceEditWnd()));
    connect(ui->actionExport,SIGNAL(triggered()),this,SLOT(openExportWnd()));
    connect(ui->actionImport,SIGNAL(triggered()),this,SLOT(openImportWnd()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(openAboutWnd()));
    connect(ui->mainTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeSlicePanel(int)));
}

CMainWindow::~CMainWindow()
{
    delete ui;
}


void CMainWindow::addNewSlicePanel(const GlobalStruct::SSlicePanelParams &params)
{
    auto tabWidget = ui->mainTabWidget;
    auto widget = new CSlicePanel(tabWidget);
    widget->setPicBoxMode(CPictureBox::EZoomMode::FixSizeCentred);//居中显示

    bool ret = widget->loadImageFromFile(params.filePath);
    if (ret)
    {
        ui->actionEditSlice->setEnabled(true);
    }
    int index = tabWidget->insertTab(tabWidget->count(),widget,params.title);
    tabWidget->setCurrentIndex(index);

}

void CMainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    //只接受图片文件
    QString filePath = event->mimeData()->urls()[0].toLocalFile();
    if(isCanDragEnterFile(filePath))
    {
        event->acceptProposedAction();//接受鼠标拖入事件
    }
    else
    {
        event->ignore();//否则不接受鼠标事件
    }
}

void CMainWindow::dropEvent(QDropEvent* event)
{
    //窗口部件放下一个对象时,调用该函数
    const QMimeData *qm=event->mimeData();//获取MIMEData
    QString filePath = qm->urls()[0].toLocalFile();
    qDebug("文件拽入:%s",filePath.toStdString().c_str());

    EnumType::EDropFileType fileType = getFileType(qm->urls()[0].toLocalFile());
    if (fileType == EnumType::EDropFileType::Image)
    {
        GlobalStruct::SSlicePanelParams params;
        params.title = GlobalVar::MAIN_WND_ADD_NEW_TB_DEFAULT_TITLE;
        params.filePath = filePath;
        params.panelType = EnumType::ESlicePanelType::Image;

        addNewSlicePanel(params);
    }
    else if (fileType == EnumType::EDropFileType::Project)
    {

    }
}

bool CMainWindow::isCanDragEnterFile(const QString &filePath)
{
  return FileUtil::isImageFile(filePath);

}
EnumType::EDropFileType CMainWindow::getFileType(const QString &filePath)
{
    if (FileUtil::isImageFile(filePath))
    {
        return EnumType::EDropFileType::Image;
    }
}

void CMainWindow::openSliceEditWnd()
{
    GlobalStruct::SSliceEditParams params;
    auto slicePanel = (CSlicePanel *)ui->mainTabWidget->currentWidget();
    //填充结构体
    params.filePath = slicePanel->getCurImgPath();
    m_sliceEditWnd->showWithParams(params);
}


void CMainWindow::closeSlicePanel(int index)
{
    ui->mainTabWidget->removeTab(index);
    if (ui->mainTabWidget->count() <= 0)
    {
        ui->actionEditSlice->setEnabled(false);
    }
}

void CMainWindow::openExportWnd()
{

    m_exportWnd->show();

}

void CMainWindow::openImportWnd()
{
    m_importWnd->show();
}


void CMainWindow::openAboutWnd()
{
    //打开模态窗口
    CAboutWnd aboutWnd;
    aboutWnd.setModal(true);
    aboutWnd.exec();
}
