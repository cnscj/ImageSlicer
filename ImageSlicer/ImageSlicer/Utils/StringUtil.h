#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QString>
class StringUtil
{
public:
    static bool isImageFile(const QString &filePath);
    static QString getFileName(const QString &fullPath,bool isExceptSuffix = false);
    static QString getBaseName(const QString &fullPath);
    static QString getFileSuffix(const QString &fullPath);
    static QString getFileDir(const QString &fullPath);
private:
    StringUtil();
};

#endif // STRINGUTIL_H
