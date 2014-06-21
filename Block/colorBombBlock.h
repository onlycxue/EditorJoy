#ifndef _COLORBOMBBLOCK_H_
#define _COLORBOMBBLOCK_H_

#include "generalBlock.h"

class ColorBombBlock : public GeneralBlock
{
public:
    ColorBombBlock();
    ColorBombBlock(ColorBombBlock &other);
    bool operator == (const BlockBase &other);
    BlockBase& operator =(const BlockBase &other);
    void setColorBombMatchType(int matchType);
    int getColorBombMatchType();
    virtual QJsonObject exportJsonObject();
    virtual void printInfo();
private:
    int _colorBombMatchType;
};


#endif
