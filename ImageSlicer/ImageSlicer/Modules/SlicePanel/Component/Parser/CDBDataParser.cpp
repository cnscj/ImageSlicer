#include "CDBDataParser.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include "ImageSlicer.h"
static const QString TEX_FILE_SUFFIX = "";
static const QString SKE_FILE_SUFFIX = "_ske";
static const QString CFG_FILE_SUFFIX = ".json";

CDBDataParser::CDBDataParser()
{

}

bool CDBDataParser::processTex(const SOutputParams &params)
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
    QString texName = StringUtil::getBaseName(params.resultData.panelData->filePath);
    QString saveFilePath = QString("%1/%2%3%4").arg(params.savePath).arg(texName).arg(TEX_FILE_SUFFIX).arg(CFG_FILE_SUFFIX);
    QJsonDocument jsonDoc(root);
    QByteArray ba = jsonDoc.toJson();
    QFile file(saveFilePath);
    if(!file.open(QIODevice::WriteOnly))
    {
       return false;
    }
    file.write(ba);
    file.close();

    return true;
}
bool CDBDataParser::processSke(const SOutputParams &params)
{
    QJsonObject root;
    QJsonArray armature;
    {
        QJsonObject armatureData1;
        QJsonArray bone;
        {
            QJsonObject boneData1;
            boneData1.insert("name","root");

            bone.push_back(boneData1);
        }

        armatureData1.insert("type","Sheet");
        armatureData1.insert("frameRate",24);
        armatureData1.insert("name","Sprite");
        armatureData1.insert("bone",bone);

        armature.push_back(armatureData1);
    }
    QJsonArray slot;
    {
        QJsonObject slotData1;
        slotData1.insert("displayIndex",-1);
        slotData1.insert("name","sheetSlot");
        slotData1.insert("parent","root");

        slot.push_back(slotData1);
    }
    QJsonArray skin;
    {
        QJsonObject skinData1;
        {
            QJsonArray skinSlotArray1;
            {
                QJsonObject skinSlotArray1Data1;
                skinSlotArray1Data1.insert("name","sheetSlot");

                skinSlotArray1.push_back(skinSlotArray1Data1);

            }
            skinData1.insert("slot",skinSlotArray1);
        }
        skin.push_back(skinData1);

    }
    QJsonArray animation;
    {
        QJsonObject animationData1;
        animationData1.insert("duration",0);
        animationData1.insert("playTimes",0);
        animationData1.insert("name","Sprite");

        animation.push_back(animationData1);
    }
    QJsonArray defaultActions;
    {
        QJsonObject defaultActionsData1;
        defaultActionsData1.insert("gotoAndPlay","Sprite");

        defaultActions.push_back(defaultActionsData1);
    }

    root.insert("frameRate",24);
    root.insert("name","NewProject");
    root.insert("version","5.5");
    root.insert("compatibleVersion","5.5");
    root.insert("armature",armature);
    root.insert("slot",slot);
    root.insert("skin",skin);
    root.insert("animation",animation);
    root.insert("defaultActions",defaultActions);

    ///
    QString texName = StringUtil::getBaseName(params.resultData.panelData->filePath);
    QString saveFilePath = QString("%1/%2%3%4").arg(params.savePath).arg(texName).arg(SKE_FILE_SUFFIX).arg(CFG_FILE_SUFFIX);
    QJsonDocument jsonDoc(root);
    QByteArray ba = jsonDoc.toJson();
    QFile file(saveFilePath);
    if(!file.open(QIODevice::WriteOnly))
    {
       return false;
    }
    file.write(ba);
    file.close();
    return true;
}

bool CDBDataParser::output(const SOutputParams &params)
{
    return (processTex(params) && processSke(params));
}
bool CDBDataParser::input(const SInputParams &params)
{
    Q_UNUSED(params);
    return false;
}
