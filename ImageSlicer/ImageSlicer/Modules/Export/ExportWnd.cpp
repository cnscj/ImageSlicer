#include "ExportWnd.h"
#include "ui_ExportWnd.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ImageSlicer.h"
#include "Modules/SlicePanel/Component/Parser/CDBDataParser.h"
#include "Modules/SlicePanel/Component/Parser/CPlistDataParser.h"
CExportWnd::CExportWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CExportWnd)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width (),this->height ());

    connect(ui->previewBtn,&QPushButton::released,this,&CExportWnd::previewFileHandle);
    connect(ui->outputBtn,&QPushButton::released,this,&CExportWnd::outPutHandle);
}

CExportWnd::~CExportWnd()
{
    delete ui;
}

void CExportWnd::showWithParams(const SShowParams &params)
{
    m_params = params;
    QWidget::show();
}


void CExportWnd::previewFileHandle()
{
    QString filePath = "";
    QString fileName = "";
    QString outPath = "";
    if (m_params.resultData.panelData)
    {
        filePath = StringUtil::getFileDir(m_params.resultData.panelData->filePath);
        fileName = StringUtil::getBaseName(m_params.resultData.panelData->filePath);
        outPath = QString("%1/%2").arg(filePath).arg(fileName);
    }
    if (ui->dbRb->isChecked())
    {
        QString fileName = QFileDialog::getExistingDirectory(this,"Select export floder ...",filePath);
        ui->savePathLe->setText(fileName);
    }else if (ui->plistRb->isChecked())
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                        ("File Save as ..."),
                        outPath,
                        (QString("Plist1.0 Files (*%1)").arg(CPlistDataParser::CFG_FILE_SUFFIX)));
        ui->savePathLe->setText(fileName);
    }
}
void CExportWnd::outPutHandle()
{
    QString savePath = ui->savePathLe->text();
    CBaseParser *parser = nullptr;
    CBaseParser::SOutputParams params;
    params.savePath = savePath;
    params.resultData.panelData = m_params.resultData.panelData;
    params.resultData.gridsList = m_params.resultData.gridsList;

    if (ui->dbRb->isChecked())
    {
        parser = new CDBDataParser();
    }
    else if(ui->plistRb->isChecked())
    {
        parser = new CPlistDataParser();
    }

    if (parser->output(params))
    {
        QMessageBox::about(this, "Information", "Export is Success!!");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Export is Failed!!");
    }

    if (parser)
    {
        delete parser;
    }
}
