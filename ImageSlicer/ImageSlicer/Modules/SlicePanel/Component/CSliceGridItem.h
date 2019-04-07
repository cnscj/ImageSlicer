#ifndef CSLICEGRIDITEM_H
#define CSLICEGRIDITEM_H

#include <QtVariantPropertyManager>

class CSliceGridItem
{
public:
    CSliceGridItem();

private:
    QMap<QtProperty *, void *> *m_pPropertyToBindValue;
};

#endif // CSLICEGRIDITEM_H
