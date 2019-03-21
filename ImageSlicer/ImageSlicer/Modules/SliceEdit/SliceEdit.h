#ifndef SLICEEDIT_H
#define SLICEEDIT_H

#include <QWidget>
#include "Config/GlobalStruct.h"

namespace Ui {
class CSliceEdit;
}

class CSliceEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CSliceEdit(QWidget *parent = 0);
    ~CSliceEdit();
public:
    void showWithParams(GlobalStruct::SSliceEditParams &params);

private:
    Ui::CSliceEdit *ui;
};

#endif // SLICEEDIT_H
