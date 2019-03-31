#include "ImgAttrListItem.h"
#include "ui_ImgAttrListItem.h"

CImgAttrListItemData::CImgAttrListItemData(const QString &name,const QString &value,const QString &unit) :
    attrName(name),attrValue(value),attrUnit(unit)
{

}

CImgAttrListItem::CImgAttrListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CImgAttrListItem)
{
    ui->setupUi(this);
}

CImgAttrListItem::~CImgAttrListItem()
{
    delete ui;
}


void CImgAttrListItem::setState(const CImgAttrListItemData &data, int pos)
{
    Q_UNUSED(pos);
    ui->attrName->setText(data.attrName);
    ui->attrValue->setText(data.attrValue);
    ui->attrUnit->setText(data.attrUnit);
}
