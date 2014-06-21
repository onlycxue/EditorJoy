#include "petBlock.h"
PetBlock::PetBlock()
{

}
PetBlock::PetBlock(PetBlock& other)
{
    _pillar = other._pillar;
    _pillarName = other._pillarName;
    _matchType = other._matchType;
    _type = other._type;
    _boxed = other._boxed;

}
bool PetBlock::operator ==(BlockBase& other)
{
    PetBlock pet = (PetBlock&)other;
    return ( _pillarName == pet._pillarName&&
            _type == pet._type&&
            _matchType == pet._matchType&&
            _boxed == pet._boxed);
}
BlockBase& PetBlock::operator=(BlockBase& other)
{
    PetBlock pet = (PetBlock&)other;
    _pillar = pet._pillar;
    _pillarName = pet._pillarName;
    _matchType = pet._matchType;
    _type = pet._type;
    _boxed = pet._boxed;
    return *this;
}
void PetBlock::setBoxedable(bool flag)
{
    _boxed = flag;
}
bool PetBlock::getBoxedable()
{
    return _boxed;
}
QJsonObject PetBlock::exportJsonObject()
{
    QJsonObject object;
    object.insert("pillar",_pillar);
    object.insert("pillarName",_pillarName);
    object.insert("type",_type);
    object.insert("matchType",_matchType);
    object.insert("boxed",_boxed);
    object.insert("blockId",_blockId);
    return object;
}
void PetBlock::printInfo()
{
    qDebug() << "{";
    qDebug() << _pillar ;
    qDebug() << _pillarName;
    qDebug() << _type;
    qDebug() << _matchType;
    qDebug() << _boxed;
    qDebug() << "}";
}




