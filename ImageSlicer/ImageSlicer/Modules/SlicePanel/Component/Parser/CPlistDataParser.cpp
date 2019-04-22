#include "CPlistDataParser.h"
#include <QtXml>
#include <QFile>
#include "ImageSlicer.h"
#include "Modules/MainUI/MainWindow.h"

const QString CPlistDataParser::CFG_FILE_SUFFIX = ".plist";

CPlistDataParser::CPlistDataParser()
{

}
void CPlistDataParser::processOutNode(QDomDocument &doc,QDomElement &element,QString nameTitle,QString name,QString valueTitle,QString value)
{
    QDomElement keyTitle = doc.createElement(nameTitle);
    QDomText keyName = doc.createTextNode(name);
    keyTitle.appendChild(keyName);
    element.appendChild(keyTitle);
    QDomElement keyValuerTitle = doc.createElement(valueTitle);
    QDomText heightValue = doc.createTextNode(value);
    keyValuerTitle.appendChild(heightValue);
    element.appendChild(keyValuerTitle);
}

bool CPlistDataParser::output(const SOutputParams &params)
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

    //打开或创建文件
    QString saveFilePath = QString("%1").arg(params.savePath);
    QFile file(saveFilePath); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::WriteOnly|QFile::Truncate))//可以用QIODevice，Truncate表示清空原来的内容
    {
        return false;
    }

    QDomDocument doc;
    //写入xml头部
    QDomProcessingInstruction instruction; //添加处理命令
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root = doc.createElement("plist");
    root.setAttribute("version","1.0");
    doc.appendChild(root);
    {
        //第一个子节点
        QDomElement rootDict = doc.createElement("dict");
        root.appendChild(rootDict);
        {
            //第一个
            {
                QDomElement framesNode = doc.createElement("key"); //创建子元素
                QDomText framesName = doc.createTextNode("frames");
                framesNode.appendChild(framesName);
                rootDict.appendChild(framesNode);

                QDomElement framesDict = doc.createElement("dict");
                rootDict.appendChild(framesDict);
                {
                    for(auto it : params.resultData.gridsList)
                    {
                        if (it->enable)
                        {
                            QDomElement frame = doc.createElement("key"); //创建子元素
                            QDomText frameName = doc.createTextNode(it->name);
                            frame.appendChild(frameName);
                            framesDict.appendChild(frame);

                            QDomElement frameDict = doc.createElement("dict");
                            framesDict.appendChild(frameDict);
                            {
                                processOutNode(doc,frameDict,"key","width","integer",QString("%1").arg(it->size.width()));
                                processOutNode(doc,frameDict,"key","height","integer",QString("%1").arg(it->size.height()));
                                processOutNode(doc,frameDict,"key","offsetX","real","0");
                                processOutNode(doc,frameDict,"key","offsetY","real","0");
                                processOutNode(doc,frameDict,"key","originalWidth","integer",QString("%1").arg(it->size.width()));
                                processOutNode(doc,frameDict,"key","originalHeight","integer",QString("%1").arg(it->size.height()));
                                processOutNode(doc,frameDict,"key","x","real",QString("%1").arg(it->pos.x()));
                                processOutNode(doc,frameDict,"key","y","real",QString("%1").arg(it->pos.y()));
                            }
                        }
                    }
                }
            }
            //第二个
            {
                QDomElement metadataNode = doc.createElement("key"); //创建子元素
                QDomText metadataName = doc.createTextNode("metadata");
                metadataNode.appendChild(metadataName);
                rootDict.appendChild(metadataNode);

                QDomElement metadataDict = doc.createElement("dict");
                rootDict.appendChild(metadataDict);
                {
                    processOutNode(doc,metadataDict,"key","format","integer","0");
                    processOutNode(doc,metadataDict,"key","realTextureFileName","string",StringUtil::getFileName(imgPath));
                    processOutNode(doc,metadataDict,"key","size","string",QString("{%1,%2}").arg(params.resultData.panelData->size.width()).arg(params.resultData.panelData->size.height()));
//                    processOutNode(doc,metadataDict,"key","smartupdate","string","");
                    processOutNode(doc,metadataDict,"key","textureFileName","string",StringUtil::getFileName(imgPath));
                }
            }

            //第三个
            {
                QDomElement texNode = doc.createElement("key"); //创建子元素
                QDomText texName = doc.createTextNode("texture");
                texNode.appendChild(texName);
                rootDict.appendChild(texNode);

                QDomElement texDict = doc.createElement("dict");
                rootDict.appendChild(texDict);
                {
                    processOutNode(doc,texDict,"key","width","integer",QString("%1").arg(params.resultData.panelData->size.width()));
                    processOutNode(doc,texDict,"key","height","integer",QString("%1").arg(params.resultData.panelData->size.height()));
                }
            }

        }
    }
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();

    return true;
}
bool CPlistDataParser::input(const SInputParams &params)
{
    CSliceImportData importData;
    auto &gridsList = importData.gridsList;
    ///////
    //打开或创建文件
    QFile file(params.openPath);
    if(!file.open(QFile::ReadOnly))
    {
      return false;
    }

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
      file.close();
      return false;
    }
    file.close();
    //
    QDomElement root = doc.documentElement(); //返回根节点
    QDomNode dictNode = root.namedItem("dict");

    QDomNode nodeKey = dictNode.namedItem("key");
    while (!nodeKey.isNull())
    {
        QDomElement nodeKeyEle = nodeKey.toElement();
        QString nodeKeyVal = nodeKeyEle.text();
        if (nodeKeyVal == "frames")
        {
            QDomNode frameDict = nodeKeyEle.nextSiblingElement("dict");
            QDomNode frameDictKey = frameDict.namedItem("key");
            while (!frameDictKey.isNull())
            {
                CSliceGridData *pData = new CSliceGridData();
                pData->name = frameDictKey.toElement().text();
                pData->enable = true;

                QDomNode frameNode = frameDictKey.nextSibling();
                QDomNode frameNodeKey = frameNode.namedItem("key");
                while (!frameNodeKey.isNull())
                {
                    QString frameDictKeyVal = frameNodeKey.toElement().text();

                    if (frameDictKeyVal == "width")
                    {
                        QDomNode valueNode = frameNodeKey.nextSibling();
                        pData->size.setWidth(valueNode.toElement().text().toInt());
                    }
                    else if (frameDictKeyVal == "height")
                    {
                        QDomNode valueNode = frameNodeKey.nextSibling();
                        pData->size.setHeight(valueNode.toElement().text().toInt());
                    }
                    else if (frameDictKeyVal == "x")
                    {
                        QDomNode valueNode = frameNodeKey.nextSibling();
                        pData->pos.setX(valueNode.toElement().text().toInt());
                    }
                    else if (frameDictKeyVal == "y")
                    {
                        QDomNode valueNode = frameNodeKey.nextSibling();
                        pData->pos.setY(valueNode.toElement().text().toInt());
                    }

                    frameNodeKey = frameNodeKey.nextSiblingElement("key");
                }

                gridsList.push_back(pData);
                frameDictKey = frameDictKey.nextSiblingElement("key");
            }
        }
        else if(nodeKeyVal == "metadata")
        {
            QDomNode metadataDict = nodeKey.nextSiblingElement("dict");
            QDomNode metadataDictKey = metadataDict.namedItem("key");
            while (!metadataDictKey.isNull())
            {
                QDomElement metadataDictKeyEle = metadataDictKey.toElement();
                QString metadataDictKeyVal = metadataDictKeyEle.text();
                if (metadataDictKeyVal == "textureFileName")
                {
                    QDomNode valueNode = metadataDictKeyEle.nextSibling();
                    importData.panelData.imagePath = QString("%1/%2").arg(StringUtil::getFileDir(params.openPath)).arg(valueNode.toElement().text());
                }

                metadataDictKey = metadataDictKey.nextSiblingElement("key");
            }
        }

        nodeKey = nodeKey.nextSiblingElement("key");
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
