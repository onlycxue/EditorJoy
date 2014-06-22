#ifndef _GROUPITEM_H_
#define _GROUPITEM_H_
#include "../Block/generalBlock.h"

#include <QJsonObject>

class GroupItem
{
public:
    GroupItem();
    GroupItem(QJsonObject& obj);
    void setMaxValue(int max);
    void setMinValue(int min);
    void setProbability(float data);
    void setBlockId(int blockId);
    int getMaxValue();
    int getMinValue();
    float getProbability();
    int getBlockId();
    GeneralBlock* getBlockItem();
    QJsonObject exportJsonObject();
    //GeneralBlock* findBlockItem();
private:
    int _max;
    int _min;
    float _probability;
    int _blockId;
    GeneralBlock* _blockItem;
   // QVector<GeneralBlock*> _blockRule;
};



#endif
