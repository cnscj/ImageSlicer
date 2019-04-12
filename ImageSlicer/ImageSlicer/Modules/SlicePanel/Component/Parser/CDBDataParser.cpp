#include "CDBDataParser.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include "ImageSlicer.h"
CDBDataParser::CDBDataParser()
{

}

bool CDBDataParser::output(const SOutputParams &params)
{
    QJsonObject root;
    QJsonArray subTexture;
    for(auto it : params.resultData.gridsList)
    {
        if (it->enable)
        {
            QJsonObject frame;
            frame.insert("name",it->name);
            frame.insert("x",it->pos.x());
            frame.insert("y",it->pos.y());
            frame.insert("width",it->size.width());
            frame.insert("height",it->size.height());

            subTexture.push_back(frame);
        }
    }

    root.insert("imagePath",StringUtil::getFileName(params.resultData.panelData->filePath));
    root.insert("name",StringUtil::getBaseName(params.resultData.panelData->filePath));
    root.insert("width",params.resultData.panelData->size.width());
    root.insert("height",params.resultData.panelData->size.height());
    root.insert("SubTexture",subTexture);
    ///
    QJsonDocument jsonDoc(root);
    QByteArray ba = jsonDoc.toJson();
    QFile file(params.savePath);
    if(!file.open(QIODevice::WriteOnly))
    {
       return false;
    }
    file.write(ba);
    file.close();

    return true;
}
bool CDBDataParser::input(const SInputParams &params)
{
    Q_UNUSED(params);
}
