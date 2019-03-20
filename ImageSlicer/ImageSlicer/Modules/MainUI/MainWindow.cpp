#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Modules/SlicePanle/SlicePanle.h"
#include "Modules/SliceEdit/SliceEdit.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    this->setAcceptDrops(true);//设置窗口启用拖动

    m_sliceEditWnd = new CSliceEdit();
    m_sliceEditWnd->hide();

    connect(ui->actionEditSlice,SIGNAL(triggered()),this,SLOT(openSliceEditWnd()));
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
    QImage image(qm->urls()[0].toLocalFile());
    qDebug("文件拽入:%s",qm->urls()[0].toLocalFile().toStdString().c_str());

    EnumType::EDropFileType fileType = getFileType(qm->urls()[0].toLocalFile());
    if (fileType == EnumType::EDropFileType::Image)
    {
        //TODO:新建一个新的窗口
        addNewSlicePanel(GlobalVar::MAIN_WND_ADD_NEW_TB_DEFAULT_TITLE);
    }
    else if (fileType == EnumType::EDropFileType::Project)
    {

    }
}

bool CMainWindow::isCanDragEnterFile(const QString &filePath)
{
   return (
            !filePath.right(3).compare("jpg",Qt::CaseInsensitive)
            || !filePath.right(3).compare("png",Qt::CaseInsensitive)
            || !filePath.right(3).compare("bmp",Qt::CaseInsensitive)
            || !filePath.right(4).compare("jpeg",Qt::CaseInsensitive)
          );

}
EnumType::EDropFileType CMainWindow::getFileType(const QString &filePath)
{
    return EnumType::EDropFileType::Image;
}

void CMainWindow::openSliceEditWnd()
{
    m_sliceEditWnd->show();
}
