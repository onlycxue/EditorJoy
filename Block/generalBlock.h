#ifndef _GENERALBLOCK_H_
#define _GENERALBLOCK_H_
#include "blockBase.h"

class GeneralBlock:public BlockBase
{
public:
    GeneralBlock();
    GeneralBlock(GeneralBlock& other);
    GeneralBlock& operator= (GeneralBlock& other);
    bool operator==(GeneralBlock& other);
    void setMatchType(int matchType);
    int getMatchType();
    virtual QJsonObject exportJsonObject();
protected:
    int _matchType;
};

#endif
