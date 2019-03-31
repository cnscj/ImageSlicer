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
     enum class ESliceType {Part,Size};

    struct SSliceCallbackParams
    {
        QPair<ESliceType ,int> horizon;
        QPair<ESliceType ,int> vertical;
        QSizeF sliceSize;
    };
    struct SShowParams
    {
        QString filePath;
        QSize imgSize;
    };
public:
    explicit CSliceEdit(QWidget *parent = 0);
    ~CSliceEdit();
public:
    void showWithParams(SShowParams &params);
private slots:
    void sliceHandle();
    void showResultText();

    void ColGridEdited(const QString &);
    void ColPixelEdited(const QString &);
    void RowGridEdited(const QString &);
    void RowPixelEdited(const QString &);
signals:
    void sliceCallback(const SSliceCallbackParams &args);
private:
    Ui::CSliceEdit *ui;
    SShowParams m_showParams;
};



#endif // SLICEEDIT_H
