#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QWidget>
#include <QMap>
#include "Component/UI/CPictureBox.h"
#include "Modules/SlicePanel/Component/ImgAttrListItem.h"

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
    struct SNewTabParams
    {
        QString title;
        QString filePath;
    };
public:
    explicit CSlicePanel(QWidget *parent = nullptr);
    ~CSlicePanel();
protected:
    enum class EActionMode{WantScale,MultipleSelect,RegionSelect};
public:
    const QString &getCurImgPath() const;
    const QSize &getCurImageSize() const;

    void setPicBoxMode(CPictureBox::EZoomMode);
signals:
    void imageDataUpdate();
public slots:
    bool loadImageFromFile(const QString &filePath);
    void sliceImageBySize(const QSizeF &size);
private slots:
    void updateImgAttrList();
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void wheelEvent(QWheelEvent * e);           //滚轮事件
    virtual void mousePressEvent(QMouseEvent *e);       //单击

private:
    void clearAttrList();
    void setAttrListProvider(const QLinkedList<CImgAttrListItemData> &);

private:
    Ui::CSlicePanel *ui;

    QString m_imageFilePath;
    QMap<EActionMode,bool>  m_flagsMap;
};

#endif // SLICEPANLE_H
