#include "colorBombBlock.h"

ColorBombBlock::ColorBombBlock()
{

}
ColorBombBlock::ColorBombBlock(ColorBombBlock &other)
{
    _pillar = other._pillar;
    _pillarName = other._pillarName;
    _type = other._type;
    _matchType = other._matchType;
    _colorBombMatchType = other._colorBombMatchType;
}
bool ColorBombBlock::operator == (const BlockBase &other)
{
    ColorBombBlock colorBomb = (ColorBombBlock&)other;
    return  (  _pillarName == colorBomb._pillarName&&
                _type == colorBomb._type&&
                _matchType == colorBomb._matchType&&
                _colorBombMatchType == colorBomb._colorBombMatchType);
}
BlockBase& ColorBombBlock::operator =(const BlockBase &other)
{
    ColorBombBlock& colorBomb = (ColorBombBlock&)other;
    _pillar = colorBomb._pillar;
    _pillarName = colorBomb._pillarName;
    _type = colorBomb._type;
    _matchType = colorBomb._matchType;
    _colorBombMatchType = colorBomb._colorBombMatchType;
    return *this;
}
void ColorBombBlock::setColorBombMatchType(int matchType)
{
    _colorBombMatchType = matchType;
}
int ColorBombBlock::getColorBombMatchType()
{
    return _colorBombMatchType;
}

QJsonObject ColorBombBlock::exportJsonObject()
{
    QJsonObject object;
    object.insert("pillar",_pillar);
    object.insert("pillarName",_pillarName);
    object.insert("type",_type);
    object.insert("matchType",_matchType);
    object.insert("colorbombmatchtype",_colorBombMatchType);
    object.insert("blockId",_blockId);
    return object;

}
void ColorBombBlock::printInfo()
{
    qDebug() << "{";
    qDebug() << _pillar ;
    qDebug() << _pillarName;
    qDebug() << _type;
    qDebug() << _matchType;
    qDebug() << _colorBombMatchType;
    qDebug() << "}";
}
