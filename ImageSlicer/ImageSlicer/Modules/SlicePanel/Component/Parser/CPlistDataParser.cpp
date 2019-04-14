#include "CPlistDataParser.h"
#include <QtXml>
#include "ImageSlicer.h"

static const QString CFG_FILE_SUFFIX = ".xml";

CPlistDataParser::CPlistDataParser()
{

}
void CPlistDataParser::processNode(QDomDocument &doc,QDomElement &element,QString nameTitle,QString name,QString valueTitle,QString value)
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
                                processNode(doc,frameDict,"key","width","integer",QString("%1").arg(it->size.width()));
                                processNode(doc,frameDict,"key","height","integer",QString("%1").arg(it->size.height()));
                                processNode(doc,frameDict,"key","offsetX","real","0");
                                processNode(doc,frameDict,"key","offsetY","real","0");
                                processNode(doc,frameDict,"key","originalWidth","integer",QString("%1").arg(it->size.width()));
                                processNode(doc,frameDict,"key","originalHeight","integer",QString("%1").arg(it->size.height()));
                                processNode(doc,frameDict,"key","x","real",QString("%1").arg(it->pos.x()));
                                processNode(doc,frameDict,"key","y","real",QString("%1").arg(it->pos.y()));
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
                    processNode(doc,metadataDict,"key","format","integer","0");
                    processNode(doc,metadataDict,"key","realTextureFileName","string",StringUtil::getFileName(params.resultData.panelData->filePath));
                    processNode(doc,metadataDict,"key","size","string",QString("{%1,%2}").arg(params.resultData.panelData->size.width()).arg(params.resultData.panelData->size.height()));
//                    processNode(doc,metadataDict,"key","smartupdate","string","");
                    processNode(doc,metadataDict,"key","textureFileName","string",StringUtil::getFileName(params.resultData.panelData->filePath));
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
                    processNode(doc,texDict,"key","width","integer",QString("%1").arg(params.resultData.panelData->size.width()));
                    processNode(doc,texDict,"key","height","integer",QString("%1").arg(params.resultData.panelData->size.height()));
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
    Q_UNUSED(params);
    return false;
}
