#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
class CSlicePanel;

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
private:
    Ui::CMainWindow *ui;

    static const QString s_tempTabName;
};

#endif // CMAINWINDOW_H
