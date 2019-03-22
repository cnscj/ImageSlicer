#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QWidget>
#include "Component/UI/CPictureBox.h"

namespace Ui {
class CSlicePanel;
}

class CSlicePanel : public QWidget
{
    Q_OBJECT

public:
    explicit CSlicePanel(QWidget *parent = nullptr);
    ~CSlicePanel();
public:
    const QString &getCurImgPath();

    void setPicBoxMode(CPictureBox::EZoomMode);

public slots:
    bool loadImageFromFile(const QString &filePath);

private:
    Ui::CSlicePanel *ui;

    QString m_imageFilePath;
};

#endif // SLICEPANLE_H
