#ifndef EXPORTWND_H
#define EXPORTWND_H

#include <QWidget>

namespace Ui {
class CExportWnd;
}

class CExportWnd : public QWidget
{
    Q_OBJECT

public:
    explicit CExportWnd(QWidget *parent = 0);
    ~CExportWnd();

private:
    Ui::CExportWnd *ui;
};

#endif // EXPORTWND_H
