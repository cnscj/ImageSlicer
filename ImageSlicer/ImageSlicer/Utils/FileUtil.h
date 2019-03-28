#ifndef FILEUTIL_H
#define FILEUTIL_H

class QString;

class FileUtil
{

public:
    static bool isImageFile(const QString &filePath);
    static QString getFileName(const QString &fullPath,bool isExceptSuffix = false);
    static QString getFileSuffix(const QString &fullPath);
    static QString getFileDir(const QString &fullPath);
private:
    FileUtil();
};

#endif // FILEUTIL_H
