#ifndef UIDUTIL_H
#define UIDUTIL_H

class QString;
class UIDUtil
{
public:
    static int GetEventUID();

    static unsigned long long GetStrUID16(const QString &str);
    static unsigned int GetStrUID8(const QString &str);
private:
    UIDUtil();
private:
    static int s_nEventUID;
};

#endif // UIDUTIL_H
