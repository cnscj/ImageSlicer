#ifndef CBASEPARSER_H
#define CBASEPARSER_H

#include "../../Models/CSliceExportData.h"
#include "../../Models/CSliceImportData.h"
class CBaseParser
{
public:
    struct SOutputParams
    {
        QString savePath;
        CSliceExportData resultData;

    };
    struct SInputParams
    {
        QString openPath;
        QWidget *widget;
    };
public:
    CBaseParser();
    virtual ~CBaseParser();
public:
    virtual bool output(const SOutputParams &params) = 0;
    virtual bool input(const SInputParams &params) = 0;
};

#endif // CBASEPARSER_H
