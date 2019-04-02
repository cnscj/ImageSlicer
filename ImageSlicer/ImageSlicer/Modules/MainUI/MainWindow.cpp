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

static const QString MAIN_WND_ADD_NEW_TB_DEFAULT_TITLE = "_Temp";


CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    m_pExportWnd = new CExportWnd();
    m_pExportWnd->setAttribute(Qt::WA_ShowModal, true);   //改为模态窗口

    m_pImportWnd = new CImportWnd();
    m_pImportWnd->setAttribute(Qt::WA_ShowModal, true);   //改为模态窗口

    ///////
    this->setAcceptDrops(true);//设置窗口启用拖动

    connect(ui->actionExport,SIGNAL(triggered()),this,SLOT(openExportWnd()));
    connect(ui->actionImport,SIGNAL(triggered()),this,SLOT(openImportWnd()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(openAboutWnd()));
    connect(ui->mainTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeSlicePanel(int)));


}

CMainWindow::~CMainWindow()
{
    delete ui;
    delete m_pExportWnd;
    delete m_pImportWnd;
}


void CMainWindow::addNewSlicePanel(const CSlicePanel::SNewTabParams &params)
{
    auto tabWidget = ui->mainTabWidget;
    auto widget = new CSlicePanel(tabWidget);
    widget->setPicBoxMode(CPictureBox::EZoomMode::AutoSize);//居中显示

    bool ret = widget->loadImageFromFile(params.filePath);
    if (ret)
    {

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
    QString fieName = FileUtil::getFileName(filePath);

    EnumType::EDropFileType fileType = getFileType(qm->urls()[0].toLocalFile());
    if (fileType == EnumType::EDropFileType::Image)
    {
        CSlicePanel::SNewTabParams params;
        params.title = fieName;
        params.filePath = filePath;

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
    return EnumType::EDropFileType::Unknow;
}


void CMainWindow::closeSlicePanel(int index)
{
    ui->mainTabWidget->removeTab(index);
    if (ui->mainTabWidget->count() <= 0)
    {

    }
}

void CMainWindow::openExportWnd()
{

    m_pExportWnd->show();

}

void CMainWindow::openImportWnd()
{
    m_pImportWnd->show();
}


void CMainWindow::openAboutWnd()
{
    //打开模态窗口
    CAboutWnd aboutWnd;
    aboutWnd.setModal(true);
    aboutWnd.exec();
}
