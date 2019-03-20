#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include <QMainWindow>
#include "Config/EnumType.h"
#include "Config/GlobalVar.h"
class QDragEnterEvent;
class QDropEvent;
class CSlicePanel;
class CSliceEdit;

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
    void addNewSlicePanel(const QString &title);

protected:
    void dragEnterEvent(QDragEnterEvent *event);//拖动进入事件
    void dropEvent(QDropEvent *event);
private:
    bool isCanDragEnterFile(const QString &filePath);
    EnumType::EDropFileType getFileType(const QString &filePath);

private slots:
    void openSliceEditWnd();


private:
    Ui::CMainWindow *ui;

    CSliceEdit *m_sliceEditWnd;
};

#endif // CMAINWINDOW_H
