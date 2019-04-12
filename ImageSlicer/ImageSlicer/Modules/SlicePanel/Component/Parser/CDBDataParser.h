#ifndef CDBDATAPARSER_H
#define CDBDATAPARSER_H

#include "CBaseParser.h"
class CDBDataParser : public CBaseParser
{
public:
    CDBDataParser();
public:
    bool output(const SOutputParams &params);
    bool input(const SInputParams &params);

};

#endif // CDBDATAPARSER_H
