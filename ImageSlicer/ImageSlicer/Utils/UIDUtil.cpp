#include "UIDUtil.h"
#include <QCryptographicHash>
#include <QString>
#include <QDebug>
int UIDUtil::s_nEventUID = 1000;

///
int UIDUtil::GetEventUID()
{
    s_nEventUID = s_nEventUID + 1;
    return s_nEventUID;
}

unsigned long long UIDUtil::GetStrUID16(const QString &str)
{
    QByteArray md5 = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    QString _16md5 = md5.toHex().mid(8,16);  //16位Md5
    return _16md5.toULongLong(NULL,16);
}

unsigned int UIDUtil::GetStrUID8(const QString &str)
{
    QByteArray md5 = QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);
    QString _8md5 = md5.toHex().mid(12,8);  //8位Md5
    return _8md5.toUInt(NULL,16);
}

UIDUtil::UIDUtil()
{

}

