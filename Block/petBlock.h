#ifndef _PETBLOCK_H_
#define _PETBLOCK_H_
#include "generalBlock.h"

class PetBlock:public GeneralBlock
{
public:
    PetBlock();
    PetBlock(PetBlock& other);
    bool operator ==(BlockBase& other);
    BlockBase& operator=(BlockBase& other);
    void setBoxedable(bool flag);
    bool getBoxedable();
    virtual QJsonObject exportJsonObject();
    virtual void printInfo();
private:
    bool _boxed;
};


#endif
