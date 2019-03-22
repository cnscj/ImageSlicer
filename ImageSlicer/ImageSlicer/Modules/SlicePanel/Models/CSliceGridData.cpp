#include "CSliceGridData.h"

CSliceGridData::CSliceGridData()
{

}


bool CSliceGridData::operator < (const CSliceGridData &data)
{
    //x位置靠左,y位置靠上的最大
    return (this->pos.x != data.pos.x) ? (this->pos.x > data.pos.x) : (this->pos.y > data.pos.y);
}
