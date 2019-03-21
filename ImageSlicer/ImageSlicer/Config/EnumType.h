#ifndef ENUMTYPE_H
#define ENUMTYPE_H

struct EnumType
{
    //拖拽文件的类型
    enum class EDropFileType
    {
        Image,
        Project
    };

    enum class ESlicePanelType
    {
        Unknow,
        Image,
        Project
    };
};

#endif // ENUMTYPE_H
