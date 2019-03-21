#ifndef SLICEPANLE_H
#define SLICEPANLE_H

#include <QWidget>

namespace Ui {
class CSlicePanel;
}

class CSlicePanel : public QWidget
{
    Q_OBJECT

public:
    explicit CSlicePanel(QWidget *parent = nullptr);
    ~CSlicePanel();
public:
    const QString &getCurImgPath();
public slots:
    bool loadImageFromFile(const QString &filePath);

private:
    Ui::CSlicePanel *ui;

    QString m_imageFilePath;
};

#endif // SLICEPANLE_H
