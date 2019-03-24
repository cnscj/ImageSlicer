#ifndef FILEUTIL_H
#define FILEUTIL_H

class QString;

class FileUtil
{

public:
    static bool isImageFile(const QString &filePath);

private:
    FileUtil();
};

#endif // FILEUTIL_H
