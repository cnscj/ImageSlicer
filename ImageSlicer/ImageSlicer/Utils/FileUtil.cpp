#include "FileUtil.h"
#include <QString>
#include <QFileInfo>

bool FileUtil::isImageFile(const QString &filePath)
{
    return (
             !filePath.right(3).compare("jpg",Qt::CaseInsensitive)
             || !filePath.right(3).compare("png",Qt::CaseInsensitive)
             || !filePath.right(3).compare("bmp",Qt::CaseInsensitive)
             || !filePath.right(4).compare("jpeg",Qt::CaseInsensitive)
           );
}

QString FileUtil::getFileName(const QString &fullPath,bool isExceptSuffix)
{
    QFileInfo info = QFileInfo(fullPath);
    if (isExceptSuffix)
    {
        return info.baseName();
    }
    return info.fileName();
}

QString FileUtil::getFileSuffix(const QString &fullPath)
{
    QFileInfo info = QFileInfo(fullPath);
    return info.suffix();
}

QString FileUtil::getFileDir(const QString &fullPath)
{
    QFileInfo info = QFileInfo(fullPath);
    return info.absolutePath();
}
