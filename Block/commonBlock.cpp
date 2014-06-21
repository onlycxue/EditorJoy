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
BlockBase& CommonBlock::operator =(BlockBase &other)
{
    CommonBlock& common = (CommonBlock&)other;
    _pillarName = common._pillarName ;
    _pillar = common._pillar ;
    _type = common._type ;
    _matchType = common._matchType ;
    _frozen = common._frozen ;
    _frozenLevel = common._frozenLevel ;
    _multiplier = common._multiplier;
    return *this;
}
bool CommonBlock::operator ==(BlockBase &other)
{
    CommonBlock& common = (CommonBlock&)other;
    return (_pillarName == common._pillarName &&
            _type == common._type &&
            _matchType == common._matchType &&
            _frozen == common._frozen &&
            _frozenLevel == common._frozenLevel &&
            _multiplier == common._multiplier);
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
    object.insert("blockId",_blockId);
    return object;
}

void CommonBlock::printInfo()
{
    qDebug() << "{";
    qDebug() << _pillar ;
    qDebug() << _pillarName;
    qDebug() << _type;
    qDebug() << _matchType;
    qDebug() << _frozen;
    qDebug() << _frozenLevel;
    qDebug() << _multiplier;
    qDebug() << "}";
}
