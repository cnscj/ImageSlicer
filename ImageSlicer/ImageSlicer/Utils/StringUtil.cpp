#include "StringUtil.h"
#include <QFileInfo>

QString StringUtil::getFileName(const QString &fullPath,bool isExceptSuffix)
{
    QFileInfo info = QFileInfo(fullPath);
    if (isExceptSuffix)
    {
        return info.baseName();
    }
    return info.fileName();
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

StringUtil::StringUtil()
{

}
