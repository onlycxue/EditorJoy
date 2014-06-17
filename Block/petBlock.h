#ifndef _PETBLOCK_H_
#define _PETBLOCK_H_
#include "generalBlock.h"

class PetBlock:public GeneralBlock
{
public:
    PetBlock();
    PetBlock(PetBlock& other);
    bool operator ==(PetBlock& other);
    PetBlock operator=(PetBlock& other);
    void setBoxedable(bool flag);
    bool getBoxedable();
    virtual QJsonObject exportJsonObject();
private:
    bool _boxed;
};


#endif
