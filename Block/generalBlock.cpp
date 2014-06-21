#include "generalBlock.h"

GeneralBlock::GeneralBlock()
{

}
GeneralBlock::GeneralBlock(GeneralBlock& other)
{
    _pillarName = other._pillarName;
    _pillar = other._pillar;
    _type = other._type;
    _matchType = other._matchType;
    _resource = other._resource;

}
BlockBase& GeneralBlock::operator= (BlockBase& other)
{
    GeneralBlock& general = (GeneralBlock&)other;
    _pillarName = general._pillarName;
    _pillar = general._pillar;
    _type = general._type;
    _matchType = general._matchType;
    _resource = general._resource;
    return *this;

}
bool GeneralBlock::operator==(BlockBase& other)
{
    GeneralBlock& general = (GeneralBlock&)other;
    if(_pillarName == general._pillarName &&
       _type == general._type && _matchType == general._matchType)
    {
        return true;
    }
    return false;
}
void GeneralBlock::setMatchType(int matchType)
{
    _matchType = matchType;
}
int GeneralBlock::getMatchType()
{
    return _matchType;
}
QJsonObject GeneralBlock::exportJsonObject()
{
    QJsonObject object;
    object.insert("pillar",_pillar);
    object.insert("pillarName",_pillarName);
    object.insert("type",_type);
    object.insert("matchType",_matchType);
    object.insert("blockId",_blockId);
    return object;
}
QString GeneralBlock::getResource()
{
    char filedir[200];
    sprintf(filedir,"%s/%s",BlockImageBasePath,_resource.toUtf8().data());
    return filedir;
}
void GeneralBlock::setResource(QString rec)
{
    _resource = rec;
}
int GeneralBlock::getBlockId()
{
    return _blockId;
}
void GeneralBlock::setBlockId(int id)
{
    _blockId = id;
}
void GeneralBlock::printInfo()
{
    qDebug() << "{";
    qDebug() << _pillar ;
    qDebug() << _pillarName;
    qDebug() << _type;
    qDebug() << _matchType;
    qDebug() << "}";

}
