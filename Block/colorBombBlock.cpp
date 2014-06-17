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
bool ColorBombBlock::operator == (const ColorBombBlock &other)
{
    return  (_pillar == other._pillar&&
    _pillarName == other._pillarName&&
    _type == other._type&&
    _matchType == other._matchType&&
    _colorBombMatchType == other._colorBombMatchType);
}
ColorBombBlock& ColorBombBlock::operator =(const ColorBombBlock &other)
{
    _pillar = other._pillar;
    _pillarName = other._pillarName;
    _type = other._type;
    _matchType = other._matchType;
    _colorBombMatchType = other._colorBombMatchType;
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
    return object;

}
