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

        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            //解析装饰物数据
            QJsonArray blocksArray = obj.take("blocks").toArray();

            qDebug() << "blocks.size :" << blocksArray.size() << endl;
            for (int i = 0;  i< blocksArray.size(); i++)
            {
                QJsonObject blocksInfo = blocksArray.at(i).toObject();
                QString name = blocksInfo.take("pillarName").toString();
                int blockType = blocksInfo.take("type").toInt();
                QString resource = blocksInfo.take("resource").toString();
                int matchType = blocksInfo.take("matchType").toInt();
                int frozenLevel = blocksInfo.take("frozenLevel").toInt();
                int multiplyFlag = blocksInfo.take("multiplier").toInt();
                bool boxed = blocksInfo.take("boxed").toBool();
                bool randomizedColor = blocksInfo.take("randomizedColor").toBool();

                char imageDir[200];
                sprintf(imageDir,"%s/%s",BlockImageBasePath,resource.toUtf8().data());
                qDebug()<< "chImageDir is " << imageDir << endl;

                QFile file(imageDir);
                if (file.exists())
                {
                    BlockItem *item = new BlockItem();

                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_frozenLevel = frozenLevel;
                    item->_multiplier = multiplyFlag;
                    item->_pillarName = name;
                    item->_boxed = boxed;
                    item->_randomizedColor = randomizedColor;
                    qDebug() << "###jsonType:###" <<item->_type<< endl;
                    item->_resource = imageDir;
                    _blocksinfo.append(item);
                }
            }
        }
    }
    jsonFile.close();
    return _blocksinfo;
}
void JsonHandle::parserRuleJson(const char * fileDir)
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

        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            //解析装饰物数据
            QJsonArray blocksArray = obj.take("rules").toArray();

            for (int i = 0;  i< blocksArray.size(); i++)
            {

                QJsonObject blocksInfo = blocksArray.at(i).toObject();
                QString pillarName = blocksInfo.take("pillarName").toString();

                if(pillarName.compare("PRRuleCommonBlock") == 0)
                {
                    QString blockType = blocksInfo.take("type").toString();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int frozenLevel = blocksInfo.take("frozenLevel").toInt();
                    int multiplyFlag = blocksInfo.take("multiplier").toInt();
                    bool frozen = blocksInfo.take("frozen").toBool();
                    int blockId = blocksInfo.take("blockId").toInt();
                    bool randomizedColor = blocksInfo.take("randomizedColor").toBool();

                    BlockItem *item = new BlockItem();
                    item->_pillarName = "PRRuleCommonBlock";
                    item->_type = blockType.toInt();
                    item->_matchType = matchType;
                    item->_frozenLevel = frozenLevel;
                    item->_multiplier = multiplyFlag;
                    item->_frozen = frozen;
                    item->_blockId = blockId;
                    item->_randomizedColor = randomizedColor;
                    _PRRuleCommonBlocks.append(item);
                }
                else if(pillarName.compare("PRRuleColorBombBlock") == 0)
                {

                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int blockId = blocksInfo.take("blockId").toInt();
                    int colorbombmatchtype = blocksInfo.take("colorbombmatchtype").toInt();

                    BlockItem *item = new BlockItem();
                    item->_pillarName = "PRRuleColorBombBlock";
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_blockId = blockId;
                    item->_colorbombmatchtype = colorbombmatchtype;
                    _PRRuleColorBombBlocks.append(item);
                }
                else if(pillarName.compare("PRRulePetBlock") == 0)
                {
                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int blockId = blocksInfo.take("blockId").toInt();
                    bool boxed = blocksInfo.take("boxed").toBool();
                    QString ruleName = blocksInfo.take("rulename").toString();

                    BlockItem *item = new BlockItem();
                    item->_pillarName = "PRRulePetBlock";
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_blockId = blockId;
                    item->_rulename = ruleName;
                    item->_boxed = boxed;
                    _PRRulePetBlocks.append(item);
                }
                else
                {
                    QString pillarName = blocksInfo.take("pillarName").toString();
                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int blockId = blocksInfo.take("blockId").toInt();

                    BlockItem *item = new BlockItem();
                    item->_pillarName = pillarName;
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_blockId = blockId;
                    _otherBlocks.append(item);
                }

            }
        }
    }
    jsonFile.close();

}
void JsonHandle::createBlockIds(QString name,BlockItem* item)
{
    if(name.compare("PRRuleCommonBlock") == 0)
    {
        for(int i = 0; i < _PRRuleCommonBlocks.size(); i++)
        {
            BlockItem  *block = _PRRuleCommonBlocks.at(i);
            if(block->_type == item->_type &&
               block->_matchType == item->_matchType &&
               block->_frozenLevel == item->_frozenLevel &&
               block->_multiplier == item->_multiplier &&
               block->_frozen == item->_frozen &&
               block->_randomizedColor == item->_randomizedColor){

                _blockIds.append(block->_blockId);
                break;
            }

        }
    }
    else if(name.compare("PRRuleColorBombBlock") == 0)
    {
        for(int i = 0; i < _PRRuleColorBombBlocks.size(); i++)
        {
            BlockItem  *block = _PRRuleColorBombBlocks.at(i);
            if(block->_type == item->_type &&
               block->_matchType == item->_matchType &&
               block->_colorbombmatchtype == item->_colorbombmatchtype){

                _blockIds.append(block->_blockId);
               break;
            }

        }
    }
    else if(name.compare("PRRulePetBlock") == 0)
    {
        for(int i = 0; i < _PRRuleColorBombBlocks.size(); i++)
        {
            BlockItem  *block = _PRRuleColorBombBlocks.at(i);
            if(block->_type == item->_type &&
               block->_matchType == item->_matchType &&
               block->_rulename == item->_rulename &&
               block->_boxed == item->_boxed){
                _blockIds.append(block->_blockId);
               break;
            }

        }
    }
    else
    {
        for(int i = 0; i < _otherBlocks.size(); i++)
        {
            BlockItem  *block = _otherBlocks.at(i);
            if(block->_type == item->_type &&
               block->_matchType == item->_matchType)
            {
                _blockIds.append(block->_blockId);
               break;
            }

        }

    }

}
void JsonHandle::exportJson(QVector<BlockLabel*> blockArray,int row,int column,const char *exportDir)
{
    //parserRuleByName(RuleConfigPath);
    parserRuleJson(RuleConfigPath);
    //获取blockId

    qDebug() << "_PRRuleCommonBlocks:" << _PRRuleCommonBlocks.size();
    qDebug() << "_PRRulePetBlocks:" << _PRRulePetBlocks.size();
    qDebug() << "_otherBlocks:" << _otherBlocks.size();
    qDebug() << "_PRRuleColorBombBlocks:" << _PRRuleColorBombBlocks.size();

    for(int i = 0 ; i < blockArray.size();i++)
    {
        QString name = blockArray.at(i)->getPropertys()->_pillarName;
        createBlockIds(name,blockArray.at(i)->getPropertys());
    }
    qDebug() <<"blockIds:"<< _blockIds.size() << endl;
    for(int i = 0 ; i < _blockIds.size() ; i++ )
    {
        printf("%d  ",_blockIds.at(i));
        if(i % column ==0)
        {
            printf("\n");
        }
    }

}

//void JsonHandle::parserRuleByName(const char* fileName)
//{
//    QFile jsonFile(fileName);
//    qDebug() << fileName << endl;
//    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug() << "open file error!" << endl;
//    }

//    QTextStream txtInput(&jsonFile);
//    QString fileStr;
//    fileStr = txtInput.readAll();
//    //解析关卡文件
//    //qDebug() << fileStr << endl;
//    QJsonParseError json_error;
//    QJsonDocument parse_doucment = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);

//    qDebug() << json_error.error << endl;
//    if(json_error.error == QJsonParseError::NoError)
//    {
//        if(parse_doucment.isObject())
//        {
//            QJsonObject obj = parse_doucment.object();
//            QJsonArray blocksArray = obj.take("rules").toArray();

//            for (int i = 0;  i< blocksArray.size(); i++)
//            {

//                QJsonObject blocksInfo = blocksArray.at(i).toObject();
//                QString pillarName = blocksInfo.take("pillarName").toString();
//                //比较常规方块
//                if(pillarName.compare("PRRuleCommonBlock") == 0)
//                {

//                    int matchType = blocksInfo.take("matchType").toInt();
//                    int frozenLevel = blocksInfo.take("frozenLevel").toInt();
//                    int multiplyFlag = blocksInfo.take("multiplier").toInt();
//                    if(multiplyFlag != 2)
//                    {
//                        multiplyFlag = 0;
//                    }
//                    int type = blocksInfo.take("type").toInt();
//                    int blockId = blocksInfo.take("blockId").toInt();

//                    BlockItem *item = new BlockItem();
//                    item->_type = type;
//                    item->_matchType = matchType;
//                    item->_frozenLevel = frozenLevel;
//                    item->_multiplier = multiplyFlag;
//                    item->_blockId = blockId;
//                    _PRRuleCommonBlocks.append(item);
//                }

//            }
//        }
//    }
//    jsonFile.close();
//}
