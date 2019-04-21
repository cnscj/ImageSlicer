#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QMap>
#include <QWidget>
#include <QMenu>

#include "Component/UI/CPictureBox.h"
#include "Component/CSliceGridsProperty.h"
#include "Modules/SlicePanel/Component/ImgAttrListItem.h"
#include "Modules/SliceEdit/SliceEdit.h"
#include "Models/CSliceExportData.h"
#include "Models/CSliceImportData.h"

class QKeyEvent;
class QWheelEvent;
class QMouseEvent;
class CGridItem;

namespace Ui {
class CSlicePanel;
}

class CSlicePanel : public QWidget
{
    Q_OBJECT
public:

public:
    explicit CSlicePanel(QWidget *parent = nullptr);
    ~CSlicePanel();
protected:
    enum class EActionMode{WantScale,MultipleSelect,RegionSelect};
public:
    const QString &getImgOriPath() const;
    QSize getImageOriSize() const;

    void setPicBoxMode(CPictureBox::EZoomMode);

    const CSlicePanelData &getPanelData();

    void updateInfos();
signals:
    void panelDataUpdate();
public slots:
    bool loadImageFromFile(const QString &filePath);
    CSliceExportData getExportData();

    bool setImportData(CSliceImportData &data);
private slots:
    void updateImgAttrList();
    void editSliceWnd();
    void editMergeGrids();
    void editRemoveGrids();
    void editSliceCallback(const CSliceEdit::SSliceCallbackParams &);
    void sliceClicked(CGridItem *);
protected slots:
    void propValueChanged(const QString &propName,const CSliceGridsData &data);
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

    CSlicePanelData m_panelData;
    QMap<EActionMode,bool>  m_flagsMap;

    QMenu *m_pSliceMenu;
    CSliceEdit *m_pSliceEditWnd;

    CSliceGridsProperty m_gridsProperty;
    bool m_isShowedGridsProperty;
};

#endif // SLICEPANLE_H
