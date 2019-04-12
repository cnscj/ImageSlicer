#include "StringUtil.h"
#include <QFileInfo>


bool StringUtil::isImageFile(const QString &filePath)
{
    return (
             !filePath.right(3).compare("jpg",Qt::CaseInsensitive)
             || !filePath.right(3).compare("png",Qt::CaseInsensitive)
             || !filePath.right(3).compare("bmp",Qt::CaseInsensitive)
             || !filePath.right(4).compare("jpeg",Qt::CaseInsensitive)
           );
}

QString StringUtil::getFileName(const QString &fullPath,bool isExceptSuffix)
{
    QFileInfo info = QFileInfo(fullPath);
    if (isExceptSuffix)
    {
        return info.baseName();
    }
    return info.fileName();
}

QString StringUtil::getBaseName(const QString &fullPath)
{
    return getFileName(fullPath,true);
}

QString StringUtil::getFileSuffix(const QString &fullPath)
{
    QFileInfo info = QFileInfo(fullPath);
    return info.suffix();
}

QString StringUtil::getFileDir(const QString &fullPath)
{
    QFileInfo info = QFileInfo(fullPath);
    return info.absolutePath();
}
