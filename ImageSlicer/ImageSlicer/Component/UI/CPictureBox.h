#ifndef CPICTUREBOX_H
#define CPICTUREBOX_H

#include <QWidget>
#include <QImage>
#include <QPixmap>


class CPictureBox : public QWidget
{
    Q_OBJECT
public:
    enum class EZoomMode {FixedSize, AutoZoom, AutoSize};

    explicit CPictureBox(QWidget *parent = nullptr);
    ~CPictureBox();
public:
    void setMode(EZoomMode mode);
    const EZoomMode &getMode() const;

    void setScale(double scale);
    double getScale() const;

    void setAnchorPoint(const QPointF &pt);
    const QPointF &getAnchorPoint() const;

    QSize getOriSize() const;
    QSize getCurSize() const;
    QPixmap *getImage();
private:
    QPixmap m_pixmap;
    double m_scale;
    QBrush m_brush;

    EZoomMode m_mode;
    QPointF m_anchorPoint;
protected:
    void paintEvent(QPaintEvent * event);

public slots:
    bool setImage(QImage &image, double scale = 1.0);
    void setBackground(QBrush brush);
};

#endif // CPICTUREBOX_H
