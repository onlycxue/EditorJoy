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

}
GeneralBlock& GeneralBlock::operator= (GeneralBlock& other)
{
    _pillarName = other._pillarName;
    _pillar = other._pillar;
    _type = other._type;
    _matchType = other._matchType;
    return *this;

}
bool GeneralBlock::operator==(GeneralBlock& other)
{
    if(_pillarName == other._pillarName && _pillar == other._pillar&&
       _type == other._type && _matchType == other._matchType)
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
    return object;
}
