#include "FileUtil.h"
#include <QString>
#include <QFileInfo>

bool FileUtil::isExists(const QString &path)
{
    QFileInfo fi(path);
    return fi.exists();
}
bool FileUtil::isFile(const QString &path)
{
    QFileInfo fi(path);
    return fi.isFile();
}
bool FileUtil::isDir(const QString &path)
{
    QFileInfo fi(path);
    return fi.isDir();
}
bool FileUtil::isRoot(const QString &path)
{
    QFileInfo fi(path);
    return fi.isRoot();
}
