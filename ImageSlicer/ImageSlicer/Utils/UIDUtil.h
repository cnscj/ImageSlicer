#ifndef UIDUTIL_H
#define UIDUTIL_H

class UIDUtil
{
public:
    static int GetEventUID();
private:
    UIDUtil();
private:
    static int s_nEventUID;
};

#endif // UIDUTIL_H
