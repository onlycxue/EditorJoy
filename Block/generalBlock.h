#ifndef _GENERALBLOCK_H_
#define _GENERALBLOCK_H_
#include "blockBase.h"
#include "../Global/globaldef.h"

class GeneralBlock:public BlockBase
{
public:
    GeneralBlock();
    GeneralBlock(GeneralBlock& other);
    virtual BlockBase& operator= (BlockBase& other);
    bool operator==(BlockBase& other);
    void setMatchType(int matchType);
    int getMatchType();
    QString getResource();
    void setResource(QString rec);
    int getBlockId();
    void setBlockId(int id);
    virtual QJsonObject exportJsonObject();
    virtual void printInfo();
protected:
    int _matchType;
    int _blockId;
    QString _resource;
};

#endif
