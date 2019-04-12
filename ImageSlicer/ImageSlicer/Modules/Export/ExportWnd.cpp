#include "ExportWnd.h"
#include "ui_ExportWnd.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ImageSlicer.h"
#include "Modules/SlicePanel/Component/Parser/CDBDataParser.h"

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
    QString outName = "";
    if (m_params.resultData.panelData)
    {
        QString filePath = StringUtil::getFileDir(m_params.resultData.panelData->filePath);
        QString fileName = StringUtil::getBaseName(m_params.resultData.panelData->filePath);
        outName = QString("%1/%2").arg(filePath).arg(fileName);
    }
    if (ui->dbRb->isChecked())
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                QString::fromLocal8Bit("文件另存为"),
                outName,
                tr("DragonBones5.5 Files (*.josn)"));
        ui->savePathLe->setText(fileName);
    }
}
void CExportWnd::outPutHandle()
{
    QString savePath = ui->savePathLe->text();
    if (ui->dbRb->isChecked())
    {
        CDBDataParser parser;
        CDBDataParser::SOutputParams params;
        params.savePath = savePath;
        params.resultData.panelData = m_params.resultData.panelData;
        params.resultData.gridsList = m_params.resultData.gridsList;

        if (parser.output(params))
        {
            QMessageBox::about(this, "Information", "Export is Success!!");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Export is Failed!!");
        }
    }
}
