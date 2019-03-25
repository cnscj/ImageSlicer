#include "CScrollArea.h"

CScrollArea::CScrollArea(QWidget *parent) : QScrollArea(parent), m_isWheelEnable(true)
{

}

CScrollArea::~CScrollArea()
{

}

void CScrollArea::setWheelScrollEnable(bool isEnable)
{
    m_isWheelEnable = isEnable;
}
bool CScrollArea::isWheelScrollEnabled()
{
    return m_isWheelEnable;
}

void CScrollArea::wheelEvent(QWheelEvent * e)
{
    if (m_isWheelEnable)
    {
        QScrollArea::wheelEvent(e);
    }
}
