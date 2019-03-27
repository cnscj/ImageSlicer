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
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();
public:
    void addNewSlicePanel(const CSlicePanel::SNewTabParams &params);

protected:
    void dragEnterEvent(QDragEnterEvent *event);//拖动进入事件
    void dropEvent(QDropEvent *event);
private:
    bool isCanDragEnterFile(const QString &filePath);
    EnumType::EDropFileType getFileType(const QString &filePath);

private slots:

    void closeSlicePanel(int index);
    void openSliceEditWnd();
    void openExportWnd();
    void openImportWnd();
    void openAboutWnd();

    void sliceEditSliceCallback(const CSliceEdit::SSliceCallbackParams &params);
private:
    Ui::CMainWindow *ui;

    CSliceEdit *m_sliceEditWnd;
    CExportWnd *m_exportWnd;
    CImportWnd *m_importWnd;
};

#endif // CMAINWINDOW_H
