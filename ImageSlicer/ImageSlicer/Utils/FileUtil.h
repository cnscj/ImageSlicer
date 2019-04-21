#ifndef FILEUTIL_H
#define FILEUTIL_H

class QString;

class FileUtil
{
public:
    static bool isExists(const QString &path);
    static bool isFile(const QString &path);
    static bool isDir(const QString &path);
    static bool isRoot(const QString &path);
private:
    FileUtil();
};

#endif // FILEUTIL_H
