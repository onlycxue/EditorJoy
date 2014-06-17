#ifndef _COMMONBLOCK_H_
#define _COMMONBLOCK_H_
#include "generalBlock.h"

class CommonBlock : public GeneralBlock
{
public:
    CommonBlock();
    CommonBlock(CommonBlock &other);
    CommonBlock& operator =(CommonBlock &other);
    bool operator ==(CommonBlock &other);
    void setFrozenable(bool flag);
    bool getFrozenable();
    void setFrozenLevel(int level);
    int getFrozenLevel();
    void setMultipliper(int level);
    int getMultipliper();
    virtual QJsonObject exportJsonObject();
private:
    bool _frozen;
    int _frozenLevel;
    int _multiplier;

};


#endif
