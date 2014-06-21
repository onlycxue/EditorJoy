#include "blockBase.h"
BlockBase::BlockBase()
{

}
BlockBase::BlockBase(BlockBase& block)
{
    _pillar = block._pillar;
    _pillarName = block._pillarName;
    _type = block._type;
}
bool BlockBase::operator==(const BlockBase &other)
{
    if(other._pillar == _pillar && other._pillarName == _pillarName
                                && other._type == _type)
    {
        return true;
    }
}

BlockBase& BlockBase::operator=(const BlockBase &other)
{
    _pillar = other._pillar;
    _pillarName = other._pillarName;
    _type = other._type;
    return *this;

}
QJsonObject BlockBase::exportJsonObject()
{
    QJsonObject object;
    object.insert("pillar",_pillar);
    object.insert("pillarName",_pillarName);
    object.insert("type",_type);
    return object;
}
void BlockBase::setPillarName(QString name)
{
    _pillarName = name;
}
void BlockBase::setPillar(QString name)
{
    _pillar = name;
}
QString BlockBase::getPillar()
{
    return _pillar;
}
QString BlockBase::getPillarName()
{
    return _pillarName;
}
void BlockBase::setType(int type)
{
    _type = type;
}
int BlockBase::getType()
{
    return _type;
}
void BlockBase::printInfo()
{
    qDebug() << "{";
    qDebug() << _pillar ;
    qDebug() << _pillarName;
    qDebug() << _type;
    qDebug() << "}";
}
