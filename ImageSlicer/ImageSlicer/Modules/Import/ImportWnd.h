#ifndef IMPORTWND_H
#define IMPORTWND_H

#include <QWidget>
class QDragEnterEvent;
class CMainWindow;
namespace Ui {
class CImportWnd;
}

class CImportWnd : public QWidget
{
    Q_OBJECT
public:
    struct SShowParams
    {
        CMainWindow *win;
    };
public:
    explicit CImportWnd(QWidget *parent = nullptr);
    ~CImportWnd();

public:
    void showWithParams(const SShowParams &params);
protected slots:
    void previewFileHandle();
    void inPutHandle();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    Ui::CImportWnd *ui;
    SShowParams m_params;
};

#endif // IMPORTWND_H
