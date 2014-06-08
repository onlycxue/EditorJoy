#include "jsonhandle.h"

JsonHandle* JsonHandle::_ptr =NULL;
JsonHandle::JsonHandle()
{

}
JsonHandle* JsonHandle::getInstance()
{
    if(!_ptr)
    {
        _ptr = new JsonHandle();
    }
    return _ptr;
}
BlockItemArray JsonHandle::parserConfigJson(const char * fileDir)
{
    QFile jsonFile(fileDir);
    qDebug() << fileDir << endl;
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "open file error!" << endl;
    }

    QTextStream txtInput(&jsonFile);
    QString fileStr;
    fileStr = txtInput.readAll();
    //解析关卡文件
    qDebug() << fileStr << endl;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);

    qDebug() << json_error.error << endl;
    if(json_error.error == QJsonParseError::NoError){
        qDebug() << "######" << endl;
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            //解析装饰物数据
            QJsonArray blocksArray = obj.take("blocks").toArray();

            qDebug() << "blocks.size :" << blocksArray.size() << endl;
            for (int i = 0;  i< blocksArray.size(); i++)
            {
                QJsonObject blocksInfo = blocksArray.at(i).toObject();
                QString resource = blocksInfo.take("resource").toString();

                char imageDir[200];
                sprintf(imageDir,"%s/%s",BlockImageBasePath,resource.toUtf8().data());
                qDebug()<< "chImageDir is " << imageDir << endl;

                QFile file(imageDir);
                if (file.exists())
                {
                    BlockItem *item = new BlockItem();
                    item->_resource = imageDir;
                    _blocksinfo.append(item);
                }
            }
        }
    }
    jsonFile.close();
    return _blocksinfo;
}
