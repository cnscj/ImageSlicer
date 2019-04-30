#include "ImportWnd.h"
#include "ui_ImportWnd.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "Modules/MainUI/MainWindow.h"
#include "Modules/SlicePanel/Component/Parser/CDBDataParser.h"
#include "Modules/SlicePanel/Component/Parser/CPlistDataParser.h"
CImportWnd::CImportWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CImportWnd)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width (),this->height ());

    connect(ui->previewBtn,&QPushButton::clicked,this,&CImportWnd::previewFileHandle);
    connect(ui->importBtn,&QPushButton::clicked,this,&CImportWnd::inPutHandle);
}

CImportWnd::~CImportWnd()
{
    delete ui;
}

void CImportWnd::showWithParams(const SShowParams &params)
{
    m_params = params;
    QWidget::show();
}


void CImportWnd::previewFileHandle()
{
    QString suffix = "";
    if (ui->dbRb->isChecked())
    {
        suffix = CDBDataParser::CFG_FILE_SUFFIX;
    }
    else if (ui->plistRb->isChecked())
    {
        suffix = CPlistDataParser::CFG_FILE_SUFFIX;
    }
    QString filePath = QFileDialog::getOpenFileName(
              this,
              "Open File ...",
              "",
             QString("Plist1.0 Files (*%1)").arg(suffix));
    ui->openPathLe->setText(filePath);


}
void CImportWnd::inPutHandle()
{
    CBaseParser *parser = nullptr;
    CBaseParser::SInputParams params;

    params.widget = m_params.win;
    params.openPath = ui->openPathLe->text();

    if (ui->dbRb->isChecked())
    {
        parser = new CDBDataParser();

    }
    else if (ui->plistRb->isChecked())
    {
        parser = new CPlistDataParser();
    }

    if (parser)
    {
        if (parser->input(params))
        {
            QMessageBox::about(this, "Information", "Import is Success!!");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Import is Failed!!");
        }

        delete parser;
    }
}

void CImportWnd::dragEnterEvent(QDragEnterEvent *event)
{
    //只接受Xml文件
    if (event->mimeData()->urls().count() > 0)
    {
        QString filePath = event->mimeData()->urls()[0].toLocalFile();
        QString suffix = "";
        if (ui->dbRb->isChecked())
        {
           suffix = CDBDataParser::CFG_FILE_SUFFIX;
        }
        else if (ui->plistRb->isChecked())
        {
           suffix = CPlistDataParser::CFG_FILE_SUFFIX;
        }

        if(suffix != "" && !StringUtil::getFileSuffix(filePath).compare(suffix.mid(1),Qt::CaseInsensitive))
        {
            event->acceptProposedAction();//接受鼠标拖入事件
            return ;
        }

    }
    event->ignore();//否则不接受鼠标事件
}
void CImportWnd::dropEvent(QDropEvent *event)
{
    QString filPath = event->mimeData()->urls()[0].toLocalFile();
    ui->openPathLe->setText(filPath);
}
