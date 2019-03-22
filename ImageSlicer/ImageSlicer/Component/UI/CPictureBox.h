#ifndef CPICTUREBOX_H
#define CPICTUREBOX_H

#include <QWidget>
#include <QImage>
#include <QPixmap>


class CPictureBox : public QWidget
{
    Q_OBJECT
public:
    enum EZoomMode {FixedSize, FixSizeCentred, AutoZoom, AutoSize};
    explicit CPictureBox(QWidget *parent = nullptr);
public:
    void setMode(EZoomMode mode);
    ~CPictureBox();
private:
    QPixmap m_pixmap;
    double m_scale;
    EZoomMode m_mode;
    QBrush m_brush;
protected:
    void paintEvent(QPaintEvent * event);

public slots:
    bool setImage(QImage &image, double scale = 1.0);
    void setBackground(QBrush brush);
};

#endif // CPICTUREBOX_H
