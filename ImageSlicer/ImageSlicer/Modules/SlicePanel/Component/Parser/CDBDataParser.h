#ifndef CDBDATAPARSER_H
#define CDBDATAPARSER_H

#include "CBaseParser.h"
class CDBDataParser : public CBaseParser
{
public:
    CDBDataParser();
protected:
    bool processTex(const SOutputParams &params);
    bool processSke(const SOutputParams &params);

public:
    bool output(const SOutputParams &params);
    bool input(const SInputParams &params);

};

#endif // CDBDATAPARSER_H
