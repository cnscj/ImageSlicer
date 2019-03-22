#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include <QMainWindow>
#include "Config/EnumType.h"
#include "Config/GlobalVar.h"
#include "Config/GlobalStruct.h"

class QDragEnterEvent;
class QDropEvent;
class CSlicePanel;
class CSliceEdit;

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
    void addNewSlicePanel(const GlobalStruct::SSlicePanelParams &params);

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

private:
    Ui::CMainWindow *ui;

    CSliceEdit *m_sliceEditWnd;
    CExportWnd *m_exportWnd;
    CImportWnd *m_importWnd;
};

#endif // CMAINWINDOW_H
