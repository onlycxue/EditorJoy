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
bool PetBlock::operator ==(PetBlock& other)
{
    return (_pillar == other._pillar&&
            _pillarName == other._pillarName&&
            _type == other._type&&
            _matchType == other._matchType&&
            _boxed == other._boxed);
}
PetBlock PetBlock::operator=(PetBlock& other)
{
    _pillar = other._pillar;
    _pillarName = other._pillarName;
    _matchType = other._matchType;
    _type = other._type;
    _boxed = other._boxed;
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
    return object;
}
