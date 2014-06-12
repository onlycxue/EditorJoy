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
                    item->init();
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
   // qDebug() << fileStr << endl;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);

    qDebug() << json_error.error << endl;
    if(json_error.error == QJsonParseError::NoError){

        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            //解析装饰物数据
             _rows = obj.take("rows").toInt();
             _column = obj.take("cols").toInt();//cols

            QJsonArray blocksArray = obj.take("rules").toArray();

            for (int i = 0;  i< blocksArray.size(); i++)
            {

                QJsonObject blocksInfo = blocksArray.at(i).toObject();
                QString pillarName = blocksInfo.take("pillarName").toString();

                if(pillarName.compare("PRRuleCommonBlock") == 0)
                {
                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int frozenLevel = blocksInfo.take("frozenLevel").toInt();
                    int multiplyFlag = blocksInfo.take("multiplier").toInt();
                    bool frozen = blocksInfo.take("frozen").toBool();
                    int blockId = blocksInfo.take("blockId").toInt();
                    bool randomizedColor = blocksInfo.take("randomizedColor").toBool();

                    BlockItem *item = new BlockItem();
                    item->_pillarName = "PRRuleCommonBlock";
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_frozenLevel = frozenLevel;
                    item->_multiplier = multiplyFlag;
                    item->_frozen = frozen;
                    item->_blockId = blockId;
                    item->_randomizedColor = randomizedColor;
                    _PRRuleCommonBlocks.append(item);
                    _rules.append(item);
                }
                else if(pillarName.compare("PRRuleColorBombBlock") == 0)
                {

                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int blockId = blocksInfo.take("blockId").toInt();
                    int colorbombmatchtype = blocksInfo.take("colorbombmatchtype").toInt();

                    BlockItem *item = new BlockItem();
                    item->init();
                    item->_pillarName = "PRRuleColorBombBlock";
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_blockId = blockId;
                    item->_colorbombmatchtype = colorbombmatchtype;
                    _PRRuleColorBombBlocks.append(item);
                    _rules.append(item);
                }
                else if(pillarName.compare("PRRulePetBlock") == 0)
                {
                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int blockId = blocksInfo.take("blockId").toInt();
                    bool boxed = blocksInfo.take("boxed").toBool();
                    QString ruleName = blocksInfo.take("rulename").toString();

                    BlockItem *item = new BlockItem();
                    item->init();
                    item->_pillarName = "PRRulePetBlock";
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_blockId = blockId;
                    item->_rulename = ruleName;
                    item->_boxed = boxed;
                    _PRRulePetBlocks.append(item);
                    _rules.append(item);
                }
                else
                {
                    //QString pillarName = blocksInfo.take("pillarName").toString();
                    int blockType = blocksInfo.take("type").toInt();
                    int matchType = blocksInfo.take("matchType").toInt();
                    int blockId = blocksInfo.take("blockId").toInt();

                    BlockItem *item = new BlockItem();
                    item->init();
                    item->_pillarName = pillarName;
                    item->_type = blockType;
                    item->_matchType = matchType;
                    item->_blockId = blockId;
                    _otherBlocks.append(item);
                    _rules.append(item);
                }

            }
        }
    }
    jsonFile.close();

}
void JsonHandle:: createBlockIds(QString name,BlockItem* item)
{

    if(name.compare("PRRuleCommonBlock") == 0)
    {
        qDebug() <<"PRRuleColorBombBlock size is "<<_PRRuleColorBombBlocks.size();
        for(int i = 0; i < _PRRuleCommonBlocks.size(); i++)
        {
            BlockItem  *block = _PRRuleCommonBlocks.at(i);
            if(block->_type == item->_type &&
               block->_frozenLevel == item->_frozenLevel &&
               block->_multiplier == item->_multiplier &&
               block->_matchType == item->_matchType &&
               block->_frozen == item->_frozen &&
               block->_randomizedColor == item->_randomizedColor){                      
                _blockIds.append(block->_blockId);
                _exportBlocksRule.append(block);
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
                _exportBlocksRule.append(block);
               break;
            }

        }
    }
    else if(name.compare("PRRulePetBlock") == 0)
    {
        for(int i = 0; i < _PRRulePetBlocks.size(); i++)
        {
            BlockItem  *block = _PRRulePetBlocks.at(i);

            //block->_rulename == item->_rulename &&
            if(block->_type == item->_type &&
               block->_matchType == item->_matchType &&
               block->_boxed == item->_boxed){
                _blockIds.append(block->_blockId);
                _exportBlocksRule.append(block);
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
                _exportBlocksRule.append(block);
               break;
            }

        }

    }

}
void JsonHandle::createGridIds()
{
    for(int i = 0; i < _blockIds.size(); i++)
    {
        if(_blockIds.at(i) == 2001)
        {
            _gridIds.append(2);
        }
        else
        {
            _gridIds.append(1);
        }
    }
}
QJsonDocument JsonHandle::exportJson(QVector<BlockLabel*> blockArray,QVector<DragLabel*> constraintArray,int row,int column,const char *exportDir)
{
    _exportBlocksRule.clear(); //防止重复导出
    _blockIds.clear();
    _gridIds.clear();
    parserRuleJson(RuleConfigPath);

    for(int i = 0 ; i < blockArray.size();i++)
    {
        QString name = blockArray.at(i)->getPropertys()->_pillarName;
        createBlockIds(name,blockArray.at(i)->getPropertys());
    }
    createGridIds();

    QJsonDocument jsonDocument;
    QJsonObject jsonLevel;
    QJsonArray blockIdArray;
    QJsonArray gridIdArray;

    QJsonArray ruleArray;
    qDebug() << "exportBlocksRule size :" << _exportBlocksRule.size();
    for(int i = 0 ; i < _exportBlocksRule.size();i++)
    {
        QJsonObject ruleObject;
        BlockItem  *block = _exportBlocksRule.at(i);

        QString name = block->_pillarName;
        if(name.compare("PRRuleCommonBlock") == 0)
        {

            ruleObject.insert("pillarName",block->_pillarName);
            ruleObject.insert("randomizedColor",block->_randomizedColor);
            ruleObject.insert("frozen",block->_frozen);
            ruleObject.insert("type",block->_type);
            ruleObject.insert("matchType",block->_matchType);
            ruleObject.insert("frozenLevel",block->_frozenLevel);
            ruleObject.insert("multiplier",block->_multiplier);
            ruleObject.insert("blockId",block->_blockId);
        }
        else if(name.compare("PRRuleColorBombBlock") == 0)
        {

            ruleObject.insert("pillarName",block->_pillarName);
            ruleObject.insert("type",block->_type);
            ruleObject.insert("matchType",block->_matchType);
            ruleObject.insert("randomizedColor",block->_randomizedColor);
            ruleObject.insert("blockId",block->_blockId);
        }
        else if(name.compare("PRRulePetBlock") == 0)
        {

            ruleObject.insert("pillarName",block->_pillarName);
            ruleObject.insert("type",block->_type);
            ruleObject.insert("matchType",block->_matchType);
            ruleObject.insert("boxed",block->_boxed);
            ruleObject.insert("blockId",block->_blockId);
        }
        else
        {

            ruleObject.insert("pillarName",block->_pillarName);
            ruleObject.insert("type",block->_type);
            ruleObject.insert("matchType",block->_matchType);
            ruleObject.insert("blockId",block->_blockId);
        }
        ruleArray.insert(i,ruleObject);
    }
    jsonLevel.insert("rules",ruleArray);
    jsonLevel.insert("cols",column);
    jsonLevel.insert("rows",row);

    for(int i = 0; i< _blockIds.size();i++)
    {
        blockIdArray.insert(i,QJsonValue(_blockIds.at(i)));
    }

    jsonLevel.insert("initialBlocks",blockIdArray);

    for(int i = 0; i < _gridIds.size();i++)
    {
        gridIdArray.insert(i,QJsonValue(_gridIds.at(i)));
    }

    jsonLevel.insert("backgroundGrid",gridIdArray);

    QJsonArray jsonConstraints;
    for(int i=0;i<constraintArray.size();i++){
        //生成json
        DragLabel * constraint = constraintArray.at(i);
        QJsonObject jsonConstraint;

        jsonConstraint.insert("xOffset", constraint->geometry().x());
        jsonConstraint.insert("yOffset", constraint->geometry().y());

        jsonConstraint.insert("resource", QString(constraint->m_strImageName.c_str()).split(".").at(0));
        jsonConstraint.insert("iOffsetToTop", 600);

        jsonConstraints.insert(i,jsonConstraint);
    }
    jsonLevel.insert("constraintSprites",jsonConstraints);

    jsonDocument.setObject(jsonLevel);


    return jsonDocument;
}
DataFormat* JsonHandle::parserExistFile(const char* fileDir)
{
    _rules.clear();
    parserRuleJson(fileDir);
    fileContent = new DataFormat;
    fileContent->_rows = _rows;
    fileContent->_column = _column;
    fileContent->_blocks = _rules;
    fileContent->_constraints = parserJsonFileForconstraint(fileDir);
    return fileContent;
}

QVector<BlockItem*> JsonHandle::parserJsonFileForBlocks(const char * fileDir)
{
    _rules.clear();
    parserRuleJson(fileDir);
    return _rules;
}
QVector<DragLabel*> JsonHandle::parserJsonFileForconstraint(const char* fileDir)
{
        _constraints.clear();
        QFile fileLevel(fileDir);
        if(!fileLevel.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //std::cout << "Open failed." << std::endl;
           // return ;
        }

        QTextStream txtInput(&fileLevel);
        QString fileStr;

        fileStr = txtInput.readAll();
        //解析关卡文件
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);

        if(json_error.error == QJsonParseError::NoError){
            if(parse_doucment.isObject())  {

                QJsonObject obj = parse_doucment.object();
                //解析装饰物数据
                QJsonArray arrayConstraints = obj.take("constraintSprites").toArray();
                //by cxue
                qDebug() << "arrayConstrains.size :" << arrayConstraints.size() << endl;
                for (int i = 0;  i< arrayConstraints.size(); i++) {
                    QJsonObject constraintInfo = arrayConstraints.at(i).toObject();
                    QString resName = constraintInfo.take("resource").toString();
                    int xOffset = constraintInfo.take("xOffset").toInt();
                    int yOffset = constraintInfo.take("yOffset").toInt();
                    int offsetToTop = constraintInfo.take("iOffsetToTop").toInt();
                    char chImageDir[200];
                    sprintf(chImageDir,"%s/%s.png",ConstraintsBasePath,resName.toUtf8().data());
                    qDebug()<< "chImageDir is " << chImageDir << endl;
                    QFile file(chImageDir);
                    if (file.exists()){
                        qDebug() << " yes the file is exit" << endl;
                        DragLabel * label = new DragLabel;
                        label->show();
                        char chImageDir[200];
                        sprintf(chImageDir,"%s/%s",ConstraintsBasePath,resName.toUtf8().data());

                        label->m_strImageName = resName.toUtf8().data();
                        QPixmap pixMap(chImageDir);
                        label->setPixmap(pixMap);
                       // label->setGeometry(xOffset,_widgetBlocksHeight - yOffset - pixMap.height(),pixMap.width(),pixMap.height());
                        label->setGeometry(xOffset,yOffset,pixMap.width(),pixMap.height());

                        _constraints.append(label);
                    }
                }
            }
        }
        fileLevel.close();
        return _constraints;
}


