#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QString>
class StringUtil
{
public:
    static QString getFileName(const QString &fullPath,bool isExceptSuffix = false);
    static QString getFileSuffix(const QString &fullPath);
    static QString getFileDir(const QString &fullPath);
private:
    StringUtil();
};

#endif // STRINGUTIL_H
