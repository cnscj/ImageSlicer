#include "FileUtil.h"
#include <QString>

bool FileUtil::isImageFile(const QString &filePath)
{
    return (
             !filePath.right(3).compare("jpg",Qt::CaseInsensitive)
             || !filePath.right(3).compare("png",Qt::CaseInsensitive)
             || !filePath.right(3).compare("bmp",Qt::CaseInsensitive)
             || !filePath.right(4).compare("jpeg",Qt::CaseInsensitive)
           );
}
