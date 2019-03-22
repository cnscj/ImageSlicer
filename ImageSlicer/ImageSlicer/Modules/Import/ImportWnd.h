#ifndef IMPORTWND_H
#define IMPORTWND_H

#include <QWidget>

namespace Ui {
class CImportWnd;
}

class CImportWnd : public QWidget
{
    Q_OBJECT

public:
    explicit CImportWnd(QWidget *parent = 0);
    ~CImportWnd();

private:
    Ui::CImportWnd *ui;
};

#endif // IMPORTWND_H
