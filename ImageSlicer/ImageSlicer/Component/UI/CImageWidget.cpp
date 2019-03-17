#include "CImageWidget.h"
#include <QFile>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
CImageWidget::CImageWidget(QWidget *parent)
    : QLabel(parent),m_curScale(1.0f),m_curBgColor(Qt::transparent),m_curAnchorPoint(0.f,0.f)
{

}

CImageWidget::~CImageWidget()
{

}

const QImage *CImageWidget::image()const
{
    return &m_curImage;
}

int CImageWidget::contentWidth()const
{
    return static_cast<int>(image()->width() * this->getScale());

}
int CImageWidget::contentHeight()const
{
    return static_cast<int>(image()->height() * this->getScale());
}
QSize CImageWidget::contentSize()const
{
    return QSize(this->contentWidth(),this->contentHeight());
}

QRect CImageWidget::contentRect()const
{
    return QRect((this->width()-this->contentWidth())/2,(this->height()-this->contentHeight())/2,this->contentWidth(),this->contentHeight());
}
QPoint CImageWidget::contentPixelPosAR(int x,int y)const
{
    auto poxelPos = this->contentPixelPos(x,y);
    auto arPos = this->getARPos();
    QPoint fixPos(poxelPos.x() - arPos.x(), arPos.y() - poxelPos.y());  //不知道为什么y轴+了1
    return fixPos;

}
QPoint CImageWidget::contentPixelPosAR(const QPoint &p)const
{
    return contentPixelPosAR(p.x(),p.y());
}

QPoint CImageWidget::contentPixelPos(int x,int y)const
{
    QPoint fixPos = contentPixmapPos(x,y);
    return QPoint(fixPos.x()/this->getScale(),fixPos.y()/this->getScale());
}
QPoint CImageWidget::contentPixelPos(const QPoint &p)const
{
    return contentPixelPos(p.x(),p.y());
}
QRgb CImageWidget::contentPixel(int x,int y)const
{
    auto scalePoint = this->contentPixelPos(x,y);
    return image()->pixel(scalePoint.x(),scalePoint.y());
}

QRgb CImageWidget::contentPixel(const QPoint &p)const
{
    return contentPixel(p.x(),p.y());
}

QPoint CImageWidget::contentPixmapPos(int x,int y)const
{
    auto imgRect = this->contentRect();
    return QPoint(x - imgRect.x(),y - imgRect.y());
}
QPoint CImageWidget::contentPixmapPos(const QPoint &p)const
{
    return contentPixmapPos(p.x(),p.y());
}

QPoint CImageWidget::contentARPos()const
{
    return QPoint(this->contentSize().width() * this->getAnchorPoint().x(),this->contentSize().height() * this->getAnchorPoint().y());
}
//
void CImageWidget::showBackgroundColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    QLabel::setAutoFillBackground(true);  //一定要这句，否则不行
    QLabel::setPalette(palette);
}

void CImageWidget::showImage(const QString &filePath)
{
    if (QFile::exists(filePath))
    {
        QLabel::setAlignment(Qt::AlignCenter);      //居中
        drawPixmap((QImage *)image(),filePath);
    }
    else
    {
        drawPixmap(nullptr);
    }

}
///
void CImageWidget::setScale(float scale)
{
    if (image()->isNull()) return ;

    m_curScale = scale;
    m_curScale = m_curScale > 15.f ? 15.f : m_curScale;
    m_curScale = m_curScale < 0.05f ? 0.05f : m_curScale;

    //TODO:放大的视图要移动到放大前鼠标所在的点,?
    QPoint mousePos = this->mapFromGlobal(this->cursor().pos());
    QPoint pos = this->contentPixmapPos(mousePos);
    emit scaled(pos);
}
float CImageWidget::getScale() const
{
    return m_curScale;
}

void CImageWidget::setAnchorPoint(const QPointF &p)
{
    if (QRectF(-1.f,-1.f,2.0f,2.0f).contains(p))
        m_curAnchorPoint = p;
}
QPointF CImageWidget::getAnchorPoint()const
{
    return m_curAnchorPoint;
}
QPoint CImageWidget::getARPos()const
{
    if (!image()->isNull())
    {
        return QPoint(image()->width() * this->getAnchorPoint().x(),image()->height() * this->getAnchorPoint().y());
    }
    return QPoint(0,0);
}

void CImageWidget::setBackground(const QColor &color)
{
    m_curBgColor = color;
}
const QColor &CImageWidget::getBackground() const
{
    return m_curBgColor;
}

//
void CImageWidget::drawPixmap(const QImage *img)
{

    if (img && !img->isNull())
    {
        QPixmap pixmap(QPixmap::fromImage(*img));
        QLabel::setPixmap(pixmap.scaled(m_curImage.width()*m_curScale, m_curImage.height()*m_curScale,Qt::KeepAspectRatio));
    }
    else
    {
        QPixmap pixmap;
        QLabel::setPixmap(pixmap);
    }
}
void CImageWidget::drawPixmap(QImage *img,const QString &filePath)
{
    if (img)
    {
        img->load(filePath);
        drawPixmap(img);
    }
}
///
void CImageWidget::paintEvent(QPaintEvent *e)
{
    //画出背景色
    QPainter painter(this);
    QRect imgRect = this->contentRect();
    painter.fillRect(imgRect,QBrush(m_curBgColor));

    QLabel::paintEvent(e);
}

void CImageWidget::wheelEvent(QWheelEvent * event)
{

    int numDegress = event->delta();
    if (numDegress > 0)
    {
        setScale(getScale()*1.15f);
    }
    else
    {
        setScale(getScale()/1.15f);
    }

    drawPixmap(image());
}

void CImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        setScale(1.0f);
        drawPixmap(image());
    }
}
