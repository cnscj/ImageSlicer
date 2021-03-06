#ifndef CPLISTDATAPARSER_H
#define CPLISTDATAPARSER_H

#include "CBaseParser.h"

class QDomDocument;
class QDomElement;

class CPlistDataParser : public CBaseParser
{
public:
    static const QString CFG_FILE_SUFFIX;
public:
    CPlistDataParser();
protected:
    void processOutNode(QDomDocument &doc,QDomElement &element,QString nameTitle,QString name,QString valueTitle,QString value);
public:
    bool output(const SOutputParams &params);
    bool input(const SInputParams &params);
};

#endif // CPLISTDATAPARSER_H
