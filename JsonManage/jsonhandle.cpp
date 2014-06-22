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

QJsonParseError JsonHandle::openJsonFile(const char* fileDir,QJsonDocument& document)
{
    QFile jsonFile(fileDir);
    _configBlocks.clear();
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
//          QMessageBox::warning(this, QObject::tr("warn"),
//                                     QObject::tr("config File is error !"),
//                                     QMessageBox::Ok);
    }

    QTextStream txtInput(&jsonFile);
    QString fileStr;
    fileStr = txtInput.readAll();
    QJsonParseError json_error;
    document = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);
    jsonFile.close();
    return json_error;
}
QVector<GeneralBlock*> JsonHandle::parserConfigJson(const char * fileDir,ConfigMode mode)
{
    _configBlocks.clear();
    QJsonDocument parse_doucment;
    QJsonParseError json_error;
    json_error = openJsonFile(fileDir,parse_doucment);

    if(json_error.error == QJsonParseError::NoError){

        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            QJsonArray blocksArray;
            if(mode == ConfigFile)
            {
                blocksArray = obj.take("blocks").toArray();
            }
            else
            {
               blocksArray = obj.take("rules").toArray();
            }
            qDebug() << "blocks.size :" << blocksArray.size() << endl;
            for (int i = 0;  i< blocksArray.size(); i++)
            {
                QJsonObject blocksInfo = blocksArray.at(i).toObject();
                QString name = blocksInfo.take("pillarName").toString();
                int blockType = blocksInfo.take("type").toInt();
                int matchType = blocksInfo.take("matchType").toInt();
                QString resource = blocksInfo.take("resource").toString();
                //int blockid = blocksInfo.take("blockId").toInt();
                if(name.compare("PRRuleCommonBlock") == 0)
                {
                    bool frozen = blocksInfo.take("frozen").toBool();
                    int frozenLevel = blocksInfo.take("frozenLevel").toInt();
                    int multiplyFlag = blocksInfo.take("multiplier").toInt();
                    CommonBlock *block = new CommonBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setFrozenable(frozen);
                    block->setFrozenLevel(frozenLevel);
                    block->setMultipliper(multiplyFlag);
                    //block->setBlockId(blockid);
                    block->setResource(resource);
                    _configBlocks.append(block);

                }
                else if(name.compare("PRRuleColorBombBlock") == 0)
                {
                    int colormatch = blocksInfo.take("colorbombmatchtype").toInt();
                    ColorBombBlock *block = new ColorBombBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setColorBombMatchType(colormatch);
                    //block->setBlockId(blockid);
                    block->setResource(resource);
                    _configBlocks.append(block);
                }
                else if(name.compare("PRRulePetBlock") == 0)
                {
                    bool boxedFlag = blocksInfo.take("boxed").toBool();
                    PetBlock *block = new PetBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setBoxedable(boxedFlag);
                    //block->setBlockId(blockid);
                    block->setResource(resource);
                    _configBlocks.append(block);

                }
                else
                {
                    GeneralBlock *block = new GeneralBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    //block->setBlockId(blockid);
                    block->setResource(resource);
                    _configBlocks.append(block);
                }
                //判断是规则文件还是配置文件
                if(mode == RuleFile)
                {
                    int blockId = blocksInfo.take("blockId").toInt();
                    _configBlocks.last()->setBlockId(blockId);

                }


        }
    }
    }

    return _configBlocks;
}
/*
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
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);

    qDebug() << json_error.error << endl;
    if(json_error.error == QJsonParseError::NoError)
    {

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
                QString name = blocksInfo.take("pillarName").toString();
                int blockType = blocksInfo.take("type").toInt();
                int matchType = blocksInfo.take("matchType").toInt();
                QString resource = blocksInfo.take("resource").toString();
                if(name.compare("PRRuleCommonBlock") == 0)
                {
                    bool frozen = blocksInfo.take("frozen").toBool();
                    int frozenLevel = blocksInfo.take("frozenLevel").toInt();
                    int multiplyFlag = blocksInfo.take("multiplier").toInt();
                    CommonBlock *block = new CommonBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setFrozenable(frozen);
                    block->setFrozenLevel(frozenLevel);
                    block->setMultipliper(multiplyFlag);
                    block->setResource(resource);
                    _configBlocks.append(block);

                }
                else if(name.compare("PRRuleColorBombBlock") == 0)
                {
                    int colormatch = blocksInfo.take("colorbombmatchtype").toInt();
                    ColorBombBlock *block = new ColorBombBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setColorBombMatchType(colormatch);
                    block->setResource(resource);
                    _configBlocks.append(block);
                }
                else if(name.compare("PRRulePetBlock") == 0)
                {
                    bool boxedFlag = blocksInfo.take("boxed").toBool();
                    PetBlock *block = new PetBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setBoxedable(boxedFlag);
                    block->setResource(resource);
                    _configBlocks.append(block);

                }
                else
                {
                    GeneralBlock *block = new GeneralBlock;
                    block->setPillarName(name);
                    block->setType(blockType);
                    block->setMatchType(matchType);
                    block->setResource(resource);
                    _configBlocks.append(block);
                }


            }
        }
    }
    jsonFile.close();

}*/

int JsonHandle:: findBlockIds(QVector<GeneralBlock*> ruleBlocks,GeneralBlock* item)
{
    if(item->getBlockId() != -1)
    {
        return item->getBlockId();
    }
    else
    {
        for(int i = 0; i < ruleBlocks.size(); i++)
        {
            if(*(ruleBlocks.at(i)) == *item)
            {
                int blockId = ruleBlocks.at(i)->getBlockId();
                item->setBlockId(blockId);
                return blockId;
            }
        }
     }
    return -3;
}
GeneralBlock* JsonHandle::findGroupBlock(int blockId)
{
    for(int i = 0 ; i < _configBlocks.size();i++)
    {
        if(_configBlocks.at(i)->getBlockId() == blockId)
        {
            return _configBlocks.at(i);
        }
    }
    return NULL;
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
QJsonDocument JsonHandle::exportJson(JsonProtocol *data)
{

    _blockIds.clear();
    parserConfigJson(RuleConfigPath,RuleFile);
    for(int i = 0 ; i < data->getBlocks().size(); i++)
    {
        //可以判断是否没有发现blockID
        _blockIds.append(findBlockIds(_configBlocks,data->getBlocks().at(i)));
    }
    //createGridIds
    for(int i = 0 ; i < _blockIds.size(); i++)
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
    QJsonDocument jsonDocument;
    QJsonObject jsonLevel;
    QJsonArray blockIdArray;
    QJsonArray gridIdArray;
    QJsonArray ruleArray;
    QJsonArray groupArray;
    QJsonArray jsonConstraints;
    //rule
    for(int i = 0; i < data->getBlocks().size(); i++)
    {
        ruleArray.insert(i,data->getBlocks().at(i)->exportJsonObject());
    }
    //add group to rule
    for(int i = 0; i < data->getGroupRules().size(); i++)
    {
        QVector<GroupItem*> items = data->getGroupRules().at(i)->getGroupItems();
        for(int j = 0 ; j < items.size(); j++)
        {
            int blockId = items.at(j)->getBlockId();
            GeneralBlock* block = findGroupBlock(blockId);
            if(!block)
            {
                ruleArray.insert(ruleArray.size(),block->exportJsonObject());
            }
        }
    }

    //blockId
    for(int i = 0; i < _blockIds.size(); i++)
    {
        blockIdArray.insert(i,_blockIds.at(i));
    }
    //grid
    for(int i = 0; i < _gridIds.size(); i++)
    {
        gridIdArray.insert(i,_gridIds.at(i));
    }
    //constraints
    for(int i = 0; i < data->getConstraints().size(); i++)
    {
        jsonConstraints.insert(i,data->getConstraints().at(i)->exportJsonObject());
    }
    //加入背景 row column
    data->getCreateData()->insertObject(jsonLevel);
    jsonLevel.insert("rules",ruleArray);
    jsonLevel.insert("initialBlocks",blockIdArray);
    jsonLevel.insert("backgroundGrid",gridIdArray);
    jsonLevel.insert("targets",data->getTargetData()->exportJsonArray());
    //add group
    qDebug() <<"#####groupSize:"<<data->getGroupRules().size() << endl;
    for(int i = 0 ; i < data->getGroupRules().size(); i++)
    {
        QJsonObject obj;
        data->getGroupRules().at(i)->insertJsonObject(obj);
        groupArray.insert(i,obj);
    }
    jsonLevel.insert("ruleBlockGroups",groupArray);
    //random add rule


    jsonDocument.setObject(jsonLevel);
    return jsonDocument;

}
JsonProtocol* JsonHandle::importJson(const char* fileDir)
{
    JsonProtocol* importData = new JsonProtocol;

    importData->setBlocks(parserConfigJson(fileDir,RuleFile));
    importData->setConstraints(parserJsonFileForconstraint(fileDir));
    importData->setCreateData(parserJsonFileForCreateData(fileDir));
    importData->setTarget(parserJsonFileForTargetData(fileDir));
    return importData;
}

/*
QJsonDocument JsonHandle::exportJson(QVector<BlockLabel*> blockArray,QVector<DragLabel*> constraintArray,
                                     int row,int column,TargetData* target,QString background)
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
    jsonLevel.insert("background",background.split(".").first());
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
    QJsonArray targetsArray;
    if(target != NULL)
    {
       QJsonObject getScore;
       getScore.insert("pillar",QString("com.king.petrescue.game.pillar.target.PRTargetScore"));
       getScore.insert("name",QString("PRTargetScore"));
       targetsArray.insert(0,getScore);

       QJsonObject getpets;
       getpets.insert("pillar",QString("com.king.petrescue.game.pillar.target.PRTargetPets"));
       getpets.insert("pillarName",QString("PRTargetPets"));
       getpets.insert("numPets",target->petNum);
       targetsArray.insert(1,getpets);

       QJsonObject getstars;
       getstars.insert("pillar",QString("com.king.petrescue.game.pillar.target.stars.PRTargetStars"));
       getstars.insert("pillarName",QString("PRTargetStars"));
       getstars.insert("star_1",target->star1Score);
       getstars.insert("star_2",target->star2Score);
       getstars.insert("star_3",target->star3Score);
       targetsArray.insert(2,getstars);

    }
    jsonLevel.insert("targets",targetsArray);

    jsonDocument.setObject(jsonLevel);


    return jsonDocument;
}
*/
//DataFormat* JsonHandle::parserExistFile(const char* fileDir)
//{
////    _rules.clear();
////    parserRuleJson(fileDir);
////    fileContent = new DataFormat;
////    fileContent->_rows = _rows;
////    fileContent->_column = _column;
////    fileContent->_blocks = _rules;
////    fileContent->_constraints = parserJsonFileForconstraint(fileDir);
////    return fileContent;

//}
CreateData* JsonHandle::parserJsonFileForCreateData(const char * fileDir)
{
    CreateData* createData = new CreateData;
    QJsonDocument parse_doucment;
    QJsonParseError json_error;
    json_error = openJsonFile(fileDir,parse_doucment);

    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            int row = obj.take("rows").toInt();
            int column = obj.take("cols").toInt();
            QString background = obj.take("background").toString();
            createData->setBackground(background);
            createData->setColumn(column);
            createData->setRow(row);
        }
    }
    else
    {
        delete createData;
        createData = NULL;
    }
    return createData;

}
TargetData* JsonHandle::parserJsonFileForTargetData(const char * fileDir)
{
    TargetData* targetData = new TargetData;
    QJsonDocument parse_doucment;
    QJsonParseError json_error;
    json_error = openJsonFile(fileDir,parse_doucment);

    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            QJsonArray targetArray = obj.take("targets").toArray();
            for(int i=0; i < targetArray.size(); i++)
            {
                QJsonObject targetObject = targetArray.at(i).toObject();
                QString name = targetObject.take("pillarName").toString();
                if(name.compare("PRTargetPets")==0)
                {
                    int petNum = targetObject.take("numPets").toInt();
                    targetData->setPetNum(petNum);
                }
                else if(name.compare("PRTargetStars") == 0)
                {
                    int star1 = targetObject.take("star_1").toInt();
                    targetData->setStar1Score(star1);
                    int star2 = targetObject.take("star_2").toInt();
                    targetData->setStar2Score(star2);
                    int star3 = targetObject.take("star_3").toInt();
                    targetData->setStar3Score(star3);
                }

            }

        }
    }
    else
    {
        delete targetData;
        targetData = NULL;
    }
    return targetData;

}
QVector<BlockItem*> JsonHandle::parserJsonFileForBlocks(const char * fileDir)
{
    _rules.clear();
    //parserRuleJson(fileDir,RuleFile);
    return _rules;
}
QVector<DragLabel*> JsonHandle::parserJsonFileForconstraint(const char* fileDir)
{
    _constraints.clear();
    QJsonDocument parse_doucment;
    QJsonParseError json_error;
    json_error = openJsonFile(fileDir,parse_doucment);

    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            QJsonArray arrayConstraints = obj.take("constraintSprites").toArray();
            //by cxue
            qDebug() << "arrayConstrains.size :" << arrayConstraints.size() << endl;
            for (int i = 0;  i< arrayConstraints.size(); i++)
            {
                QJsonObject constraintInfo = arrayConstraints.at(i).toObject();
                QString resName = constraintInfo.take("resource").toString();
                int xOffset = constraintInfo.take("xOffset").toInt();
                int yOffset = constraintInfo.take("yOffset").toInt();
                int offsetToTop = constraintInfo.take("iOffsetToTop").toInt();
                char chImageDir[200];
                sprintf(chImageDir,"%s.png",ConstraintsBasePath,resName.toUtf8().data());
                qDebug()<< "chImageDir is " << chImageDir << endl;
                QFile file(chImageDir);
                if (file.exists())
                {
                    DragLabel * label = new DragLabel;
                    label->show();
                    label->setImage(resName);
                    QPixmap pixMap(chImageDir);
                    // label->setGeometry(xOffset,_widgetBlocksHeight - yOffset - pixMap.height(),pixMap.width(),pixMap.height());
                    label->setGeometry(xOffset,yOffset,pixMap.width(),pixMap.height());
                    _constraints.append(label);

                }
            }
        }
    }
    return _constraints;
}
QJsonArray JsonHandle::parserJsonFileForGrouprule(const char *fileDir)
{
    QJsonDocument parse_doucment;
    QJsonParseError json_error;
    QJsonArray groupArray;
    json_error = openJsonFile(fileDir,parse_doucment);

    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            groupArray = obj.take("ruleBlockGroups").toArray();
            return groupArray;
        }
    }
    return groupArray;
}

