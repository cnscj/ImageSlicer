#include "CPictureBox.h"
#include <QPainter>

static const int IMAGE_WIDTH = 160;
static const int IMAGE_HEIGHT = 120;
static const QSize IMAGE_SIZE = QSize(IMAGE_WIDTH, IMAGE_HEIGHT);

CPictureBox::CPictureBox(QWidget *parent) : QWidget(parent)
{
    m_pixmap = QPixmap(IMAGE_SIZE);
    m_pixmap.fill();
    m_scale = 1.0;
    m_brush = QBrush(Qt::white);
    m_mode = EZoomMode::FixedSize;
    m_anchorPoint = QPointF(0.5,0.5);

}


void CPictureBox::setMode(EZoomMode mode)
{
    m_mode = mode;
    if(m_mode == EZoomMode::AutoSize)
    {
        setFixedSize(m_pixmap.size() * m_scale);
    }
    else
    {
        setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        setMinimumSize(0, 0);
    }
    update();
}
const CPictureBox::EZoomMode &CPictureBox::getMode() const
{
    return m_mode;
}

void CPictureBox::setScale(double scale)
{
    m_scale = scale;
    update();
}
double CPictureBox::getScale() const
{
    return m_scale;
}

void CPictureBox::setAnchorPoint(const QPointF &pt)
{
    m_anchorPoint = pt;
    update();
}
const QPointF &CPictureBox::getAnchorPoint() const
{
    return m_anchorPoint;
}

/////

void CPictureBox::setBackground(QBrush brush)
{
    m_brush = brush;
    update();
}

QSize CPictureBox::getOriSize() const
{
    return m_pixmap.size();
}

QSize CPictureBox::getCurSize() const
{
    return m_pixmap.size() * m_scale;
}
////
bool CPictureBox::setImage(QImage &image, double scale)
{
    if(image.isNull())
    {
        return false;
    }
    m_pixmap = QPixmap::fromImage(image);
    m_scale = qBound(0.01, scale, 100.0);
    if(m_mode == EZoomMode::AutoSize)
    {
        setFixedSize(m_pixmap.size() * m_scale);
    }
    update();
    return true;
}

void CPictureBox::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBackground(m_brush);
    painter.eraseRect(rect());

    double window_width, window_height;
    double image_width, image_height;
    double r1, r2, r;
    double offset_x, offset_y;
    window_width = width();
    window_height = height();
    image_width = m_pixmap.width();
    image_height = m_pixmap.height();

    switch (m_mode)
    {
    case EZoomMode::FixedSize:
        offset_x = (window_width - m_scale * image_width) * m_anchorPoint.x();
        offset_y = (window_height - m_scale * image_height) * m_anchorPoint.y();
        painter.translate(offset_x, offset_y);
        painter.scale(m_scale, m_scale);
        painter.drawPixmap(0, 0, m_pixmap);
        break;
    case EZoomMode::AutoSize:
        this->setFixedSize(m_pixmap.size() * m_scale);
        painter.scale(m_scale, m_scale);
        painter.drawPixmap(0, 0, m_pixmap);
        break;
    case EZoomMode::AutoZoom:
        r1 = window_width / image_width;
        r2 = window_height / image_height;
        r = qMin(r1, r2);
        offset_x = (window_width - r * image_width) * m_anchorPoint.x();
        offset_y = (window_height - r * image_height) * m_anchorPoint.y();
        painter.translate(offset_x, offset_y);
        painter.scale(r, r);
        painter.drawPixmap(0, 0, m_pixmap);
        break;
    }
}

CPictureBox::~CPictureBox()
{

}
