#ifndef SLICINGITEM_H
#define SLICINGITEM_H

#include <QWidget>

namespace Ui {
class CSlicingItem;
}

class CSlicingItem : public QWidget
{
    Q_OBJECT

public:
    explicit CSlicingItem(QWidget *parent = nullptr);
    ~CSlicingItem();
private:
    void setSelected(bool val);

private:
    Ui::CSlicingItem *ui;
};

#endif // SLICINGITEM_H
