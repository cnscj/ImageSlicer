#ifndef ABOUTWND_H
#define ABOUTWND_H

#include <QDialog>

namespace Ui {
class CAboutWnd;
}

class CAboutWnd : public QDialog
{
    Q_OBJECT

public:
    explicit CAboutWnd(QWidget *parent = 0);
    ~CAboutWnd();
protected slots:
    void clickOk();

private:
    Ui::CAboutWnd *ui;
};

#endif // ABOUTWND_H
