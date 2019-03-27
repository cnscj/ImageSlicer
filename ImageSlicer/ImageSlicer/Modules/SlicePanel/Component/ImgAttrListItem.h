#ifndef IMGATTRLISTITEM_H
#define IMGATTRLISTITEM_H

#include <QWidget>

namespace Ui {
class CImgAttrListItem;
}

class CImgAttrListItemData
{
public:
    QString attrName;
    QString attrValue;
    QString attrUnit;

    CImgAttrListItemData(const QString &name,const QString &value,const QString &unit);
};

class CImgAttrListItem : public QWidget
{
    Q_OBJECT
public:
    explicit CImgAttrListItem(QWidget *parent = 0);
    ~CImgAttrListItem();
public:
    void setState(const CImgAttrListItemData &data, int pos);
private:
    Ui::CImgAttrListItem *ui;
};

#endif // IMGATTRLISTITEM_H
