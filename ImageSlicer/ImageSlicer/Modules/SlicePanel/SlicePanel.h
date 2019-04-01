#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QMap>
#include <QWidget>
#include <QMenu>

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
    const QString &getImgOriPath() const;
    QSize getImageOriSize() const;

    void setPicBoxMode(CPictureBox::EZoomMode);
signals:
    void imageDataUpdate();
public slots:
    bool loadImageFromFile(const QString &filePath);
    void sliceImageBySize(const QSizeF &size);
private slots:
    void updateImgAttrList();
    void editeSlice();
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void wheelEvent(QWheelEvent * e);           //滚轮事件
    virtual void mousePressEvent(QMouseEvent *e);       //单击
    virtual void contextMenuEvent(QContextMenuEvent *e);//右键菜单
private:
    void clearAttrList();
    void setAttrListProvider(const QLinkedList<CImgAttrListItemData> &);

private:
    Ui::CSlicePanel *ui;

    QString m_imageFilePath;
    QMap<EActionMode,bool>  m_flagsMap;

    QMenu m_sliceMenu;
};

#endif // SLICEPANLE_H
