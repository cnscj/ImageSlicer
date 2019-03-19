#ifndef SLICEEDIT_H
#define SLICEEDIT_H

#include <QWidget>

namespace Ui {
class CSliceEdit;
}

class CSliceEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CSliceEdit(QWidget *parent = 0);
    ~CSliceEdit();

private:
    Ui::CSliceEdit *ui;
};

#endif // SLICEEDIT_H
