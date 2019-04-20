#ifndef EXPORTWND_H
#define EXPORTWND_H
#include "Modules/SlicePanel/Models/CSliceExportData.h"
#include <QWidget>

namespace Ui {
class CExportWnd;
}

class CExportWnd : public QWidget
{
    Q_OBJECT
public:
    struct SShowParams
    {
        CSliceExportData resultData;
    };
public:
    explicit CExportWnd(QWidget *parent = 0);
    ~CExportWnd();
public:
    void showWithParams(const SShowParams &params);
protected slots:
    void previewFileHandle();
    void outPutHandle();

private:
    Ui::CExportWnd *ui;
    SShowParams m_params;
};

#endif // EXPORTWND_H
