#include "UIDUtil.h"

 int UIDUtil::s_nEventUID = 1000;

///
int UIDUtil::GetEventUID()
{
    s_nEventUID = s_nEventUID + 1;
    return s_nEventUID;
}


UIDUtil::UIDUtil()
{

}

