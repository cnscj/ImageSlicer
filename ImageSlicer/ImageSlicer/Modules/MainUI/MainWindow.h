#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include <QMainWindow>
#include "ImageSlicer.h"
#include "Modules/SliceEdit/SliceEdit.h"
#include "Modules/SlicePanel/SlicePanel.h"

class QDragEnterEvent;
class QDropEvent;

class CExportWnd;
class CImportWnd;

struct SSlicePanelParams;

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    struct SNewTabParams
    {
        QString title;
        QString filePath;
    };
public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();
public:
    CSlicePanel *addNewSlicePanel(const CMainWindow::SNewTabParams &params);

protected:
    void dragEnterEvent(QDragEnterEvent *event);//拖动进入事件
    void dropEvent(QDropEvent *event);
private:
    bool isCanDragEnterFile(const QString &filePath);
    EnumType::EDropFileType getFileType(const QString &filePath);

private slots:

    void closeSlicePanel(int index);
    void openExportWnd();
    void openImportWnd();
    void openAboutWnd();
    void closeMainWnd();

private:
    Ui::CMainWindow *ui;

    CExportWnd *m_pExportWnd;
    CImportWnd *m_pImportWnd;
};

#endif // CMAINWINDOW_H
