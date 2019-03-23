#include "CSliceGridData.h"
#include <QCryptographicHash>
#include <QByteArray>
#include "ImageSlicer.h"
CSliceGridData::CSliceGridData()
{

}

uint CSliceGridData::getUID() const
{
    QString propsStr = QString("%1_%2_%3_%4").
            arg(this->pos.x()).arg(this->pos.y()).
            arg(this->size.width()).arg(this->size.height());
    return UIDUtil::GetStrUID8(propsStr);
}

QRect CSliceGridData::getRect() const
{
    return QRect(this->pos,this->size);
}

bool CSliceGridData::operator <(const CSliceGridData &data) const
{
    //x位置靠左,y位置靠上的最大
    return (this->pos.x() != data.pos.x()) ? (this->pos.x() > data.pos.x()) : (this->pos.y() > data.pos.y());
}

bool CSliceGridData::operator ==(const CSliceGridData &data) const
{
    return ((this->pos == data.pos) && (this->size == data.size));
}
