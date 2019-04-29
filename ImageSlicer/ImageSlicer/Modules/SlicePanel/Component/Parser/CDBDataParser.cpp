#include "CDBDataParser.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "ImageSlicer.h"
#include "Modules/MainUI/MainWindow.h"
static const QString TEX_FILE_SUFFIX = "";
static const QString SKE_FILE_SUFFIX = "_ske";
const QString CDBDataParser::CFG_FILE_SUFFIX = ".json";

CDBDataParser::CDBDataParser()
{

}

bool CDBDataParser::processOutTex(const SOutputParams &params)
{
    //图像导出
    QString imgPath = params.resultData.panelData->imagePath;
    if (!FileUtil::isExists(imgPath))
    {
        QPixmap *pPixmap = params.resultData.panelData->pPixmap;
        if (pPixmap)
        {
            //图像保存
            QString imgSavePath = QString("%1/%2.png").arg(StringUtil::getFileDir(params.resultData.panelData->openPath)).arg(StringUtil::getBaseName(params.resultData.panelData->openPath));
            pPixmap->save(imgSavePath);
        }
        else
        {
            return false;
        }
    }
    //数据导出
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

    root.insert("imagePath",StringUtil::getFileName(imgPath));
    root.insert("name",StringUtil::getBaseName(imgPath));
    root.insert("width",params.resultData.panelData->size.width());
    root.insert("height",params.resultData.panelData->size.height());
    root.insert("SubTexture",subTexture);
    ///
    QString texName = StringUtil::getBaseName(imgPath);
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
bool CDBDataParser::processOutSke(const SOutputParams &params)
{
    QString texName = StringUtil::getBaseName(params.resultData.panelData->imagePath);
    QString saveFilePath = QString("%1/%2%3%4").arg(params.savePath).arg(texName).arg(SKE_FILE_SUFFIX).arg(CFG_FILE_SUFFIX);
    if (FileUtil::isExists(saveFilePath))
    {
        return true;
    }
    ////
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
    return (processOutTex(params));
}
bool CDBDataParser::input(const SInputParams &params)
{
    CSliceImportData importData;
    auto &gridsList = importData.gridsList;

    //////
    //解析
    QFile loadFile(params.openPath);

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        return false;
    }

    QJsonObject rootObj = jsonDoc.object();
    QString imgName = rootObj.value("imagePath").toString();
    importData.panelData.imagePath = QString("%1/%2").arg(StringUtil::getFileDir(params.openPath)).arg(imgName);

    if(rootObj.contains("SubTexture"))
    {
       QJsonArray subArray = rootObj.value("SubTexture").toArray();
       for(int i = 0; i< subArray.size(); i++)
       {
            QJsonObject nodeObj = subArray.at(i).toObject();

            CSliceGridData *pData = new CSliceGridData();
            pData->name = nodeObj.value("name").toString();
            pData->pos.setX(nodeObj.value("x").toInt());
            pData->pos.setY(nodeObj.value("y").toInt());
            pData->size.setWidth(nodeObj.value("width").toInt());
            pData->size.setHeight(nodeObj.value("height").toInt());
            pData->enable = true;

            gridsList.push_back(pData);
       }
    }

    ///////
    auto mainWin = static_cast<CMainWindow *>(params.widget);
    CMainWindow::SNewTabParams tabParams;
    tabParams.title = StringUtil::getFileName(importData.panelData.imagePath);

    auto tab = mainWin->addNewSlicePanel(tabParams);
    bool ret =  tab->setImportData(importData);

    for (auto it: gridsList)
    {
        delete it;
    }

    return ret;
}
