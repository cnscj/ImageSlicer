#ifndef CBASEPARSER_H
#define CBASEPARSER_H

#include "../../Models/CSliceResultData.h"
class CBaseParser
{
public:
    struct SOutputParams
    {
        QString savePath;
        CSliceResultData resultData;

    };
    struct SInputParams
    {

    };
public:
    CBaseParser();
    virtual ~CBaseParser();
public:
    virtual bool output(const SOutputParams &params) = 0;
    virtual bool input(const SInputParams &params) = 0;
};

#endif // CBASEPARSER_H
