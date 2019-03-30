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
        QPoint gridNum;
        QSize gridSize;
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
    QSizeF calculateSliceSize();

    bool fillCallbackParams(SSliceCallbackParams &args);
private:
    Ui::CSliceEdit *ui;
    SShowParams m_showParams;
};



#endif // SLICEEDIT_H
