#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QWidget>

namespace Ui {
class CSlicePanle;
}

class CSlicePanle : public QWidget
{
    Q_OBJECT

public:
    explicit CSlicePanle(QWidget *parent = nullptr);
    ~CSlicePanle();

private:
    Ui::CSlicePanle *ui;
};

#endif // SLICEPANLE_H
