#include "commonBlock.h"

CommonBlock::CommonBlock()
{

}
CommonBlock::CommonBlock(CommonBlock &other)
{
    _pillarName = other._pillarName ;
    _pillar = other._pillar ;
    _type = other._type ;
    _matchType = other._matchType ;
    _frozen = other._frozen ;
    _frozenLevel = other._frozenLevel ;
    _multiplier = other._multiplier;
}
CommonBlock& CommonBlock::operator =(CommonBlock &other)
{
    _pillarName = other._pillarName ;
    _pillar = other._pillar ;
    _type = other._type ;
    _matchType = other._matchType ;
    _frozen = other._frozen ;
    _frozenLevel = other._frozenLevel ;
    _multiplier = other._multiplier;
    return *this;
}
bool CommonBlock::operator ==(CommonBlock &other)
{
    return (_pillarName == other._pillarName &&
            _pillar == other._pillar &&
            _type == other._type &&
            _matchType == other._matchType &&
            _frozen == other._frozen &&
            _frozenLevel == other._frozenLevel &&
            _multiplier == other._multiplier);
}
void CommonBlock::setFrozenable(bool flag)
{
    _frozen = flag;
}
bool CommonBlock::getFrozenable()
{
    return _frozen;
}
void CommonBlock::setFrozenLevel(int level)
{
    _frozenLevel = level;
}
int CommonBlock::getFrozenLevel()
{
    return _frozenLevel;
}
void CommonBlock::setMultipliper(int level)
{
    _multiplier = level;
}
int CommonBlock::getMultipliper()
{
    return _multiplier;
}

QJsonObject CommonBlock::exportJsonObject()
{
    QJsonObject object;
    object.insert("pillar",_pillar);
    object.insert("pillarName",_pillarName);
    object.insert("type",_type);
    object.insert("frozen",_frozen);
    object.insert("frozenLevel",_frozenLevel);
    object.insert("multiplier",_multiplier);
    return object;
}
