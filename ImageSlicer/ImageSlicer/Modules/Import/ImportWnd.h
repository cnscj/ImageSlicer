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
    struct SShowParams
    {

    };
public:
    explicit CImportWnd(QWidget *parent = 0);
    ~CImportWnd();

public:
    void showWithParams();

private:
    Ui::CImportWnd *ui;
};

#endif // IMPORTWND_H
