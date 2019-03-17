#ifndef CIMAGEWIDGET_H
#define CIMAGEWIDGET_H

#include <QLabel>
class CImageWidget: public QLabel
{
    Q_OBJECT
public:
    explicit CImageWidget(QWidget *parent=nullptr);
    ~CImageWidget();
signals:
    void scaled(QPoint);
public:
    const QImage *image()const;
    int contentWidth()const;
    int contentHeight()const;
    QSize contentSize()const;
    QRect contentRect()const;                       //位图矩形区域,在此widget下的相对坐标
    QPoint contentPixelPosAR(int x,int y)const;
    QPoint contentPixelPosAR(const QPoint &p)const;
    QPoint contentPixelPos(int x,int y)const;       //鼠标坐标映射到pixel坐标,不受锚点影响,与Scale相关
    QPoint contentPixelPos(const QPoint &p)const;
    QPoint contentPixmapPos(int x,int y)const;      //鼠标坐标映射到pixmap坐标,不受锚点影响,与Scale无关
    QPoint contentPixmapPos(const QPoint &p)const;
    QRgb  contentPixel(int x,int y)const;
    QRgb  contentPixel(const QPoint &p)const;
    QPoint contentARPos()const;
public:
   void showBackgroundColor(const QColor &color);
   void showImage(const QString &filePath);
public:
   void setScale(float scale);
   float getScale()const;

   void setAnchorPoint(const QPointF &p);
   QPointF getAnchorPoint() const;
   QPoint getARPos()const;

   void setBackground(const QColor &color);
   const QColor &getBackground()const;
protected:
   void drawPixmap(const QImage *img);
   void drawPixmap(QImage *img,const QString &filePath);
protected:
   virtual void paintEvent(QPaintEvent *e);
   virtual void mousePressEvent(QMouseEvent *event);        //单击
   virtual void wheelEvent(QWheelEvent * event);           //滚轮事件
private:
   QImage m_curImage;
   float m_curScale;
   QColor m_curBgColor;
   QPointF  m_curAnchorPoint;


};

#endif // CIMAGEWIDGET_H
