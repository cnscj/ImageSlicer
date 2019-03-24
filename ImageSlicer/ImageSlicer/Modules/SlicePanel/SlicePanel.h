#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QWidget>
#include <QMap>
#include "Component/UI/CPictureBox.h"

class QKeyEvent;
class QWheelEvent;
class QMouseEvent;

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
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void wheelEvent(QWheelEvent * e);           //滚轮事件
    virtual void mousePressEvent(QMouseEvent *e);       //单击
private:
    Ui::CSlicePanel *ui;

    QString m_imageFilePath;
    QMap<QString,bool>  m_flagsMap;
};

#endif // SLICEPANLE_H
