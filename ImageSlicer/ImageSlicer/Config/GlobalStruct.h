#ifndef GLOBALSTRUCT_H
#define GLOBALSTRUCT_H
//只支持简单类型的全局结构体定义,不要嵌套结构体,
//复合结构体最好不要在此定义
#include <QString>
#include "EnumType.h"

struct GlobalStruct
{
    struct SSlicePanelParams
    {
        QString title;
        QString filePath;
        EnumType::ESlicePanelType panelType;
    };

    struct SSliceEditParams
    {
        QString filePath;
    };
};

#endif // GLOBALSTRUCT_H
