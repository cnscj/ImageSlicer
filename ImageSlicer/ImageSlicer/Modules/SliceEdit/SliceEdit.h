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
    struct SSliceCallbackParams
    {
        QString test;
        QWidget *panel;
    };
    struct SShowParams
    {
        QString filePath;
        QWidget *panel;
    };
public:
    explicit CSliceEdit(QWidget *parent = 0);
    ~CSliceEdit();
public:
    void showWithParams(SShowParams &params);
private slots:
    void sliceHandle();
signals:
    void sliceCallback(const SSliceCallbackParams &args);
private:
    Ui::CSliceEdit *ui;
    SShowParams m_showParams;
};



#endif // SLICEEDIT_H
