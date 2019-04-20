#ifndef CPROJECTDATAPARSER_H
#define CPROJECTDATAPARSER_H

#include "CBaseParser.h"
class CProjectDataParser : public CBaseParser
{
public:
    static const QString CFG_FILE_SUFFIX;
public:
    CProjectDataParser();
public:
    bool output(const SOutputParams &params);
    bool input(const SInputParams &params);
};

#endif // CPROJECTDATAPARSER_H
