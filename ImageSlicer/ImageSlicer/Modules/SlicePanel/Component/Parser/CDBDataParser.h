#ifndef CDBDATAPARSER_H
#define CDBDATAPARSER_H

#include "CBaseParser.h"
class CDBDataParser : public CBaseParser
{
public:
    static const QString CFG_FILE_SUFFIX;
public:
    CDBDataParser();
protected:
    bool processOutTex(const SOutputParams &params);
    bool processOutSke(const SOutputParams &params);

public:
    bool output(const SOutputParams &params);
    bool input(const SInputParams &params);

};

#endif // CDBDATAPARSER_H
