#ifndef _COLORBOMBBLOCK_H_
#define _COLORBOMBBLOCK_H_

#include "generalBlock.h"

class ColorBombBlock : public GeneralBlock
{
public:
    ColorBombBlock();
    ColorBombBlock(ColorBombBlock &other);
    bool operator == (const ColorBombBlock &other);
    ColorBombBlock& operator =(const ColorBombBlock &other);
    void setColorBombMatchType(int matchType);
    int getColorBombMatchType();
    virtual QJsonObject exportJsonObject();
private:
    int _colorBombMatchType;
};


#endif
