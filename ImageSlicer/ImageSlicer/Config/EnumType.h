#ifndef ENUMTYPE_H
#define ENUMTYPE_H

struct EnumType
{
    //拖拽文件的类型
    enum class EDropFileType
    {
        Unknow,
        Image,
        DBFile,
        Plist,
        Project
    };

    enum class ESlicePanelType
    {
        Unknow,
        Image,
        DBFile,
        Plist,
        Project
    };
};

#endif // ENUMTYPE_H
