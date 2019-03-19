#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void openSliceEditWnd();


private:
    Ui::CMainWindow *ui;

    CSliceEdit *m_sliceEditWnd;

    static const QString s_tempTabName;
};

#endif // CMAINWINDOW_H
