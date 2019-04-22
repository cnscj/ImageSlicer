#ifndef CSLICEPANELDATA_H
#define CSLICEPANELDATA_H

#include <QPixmap>
#include <QString>
#include <QSize>
class CSlicePanelData
{
public:
    QString projectName;
    QString openPath;

    QPixmap *pPixmap;
    QString imagePath;
    QSize size;

public:
    CSlicePanelData();
};

#endif // CSLICEPANELDATA_H
