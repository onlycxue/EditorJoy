#include "groupitem.h"

GroupItem::GroupItem()
{
    //_blockRule = JsonHandle::getInstance()->parserConfigJson(RuleConfigPath,
    _max = -1;
    _min = -1;
    //JsonHandle::RuleFile);
    _blockItem = NULL;
}
GroupItem::GroupItem(QJsonObject& obj)
{
    //_blockRule = JsonHandle::getInstance()->parserConfigJson(RuleConfigPath,
                                                        //JsonHandle::RuleFile);
    _max = -1;
    _min = -1;
    _max = obj.take("max").toInt();
    _min = obj.take("min").toInt();
    _probability = obj.take("probability").toInt();
    _blockId = obj.take("blockId").toInt();

}
void GroupItem::setMaxValue(int max)
{
    _max = max;
}
void GroupItem::setMinValue(int min)
{
    _min = min;
}
void GroupItem::setProbability(float data)
{
    _probability = data;
}
void GroupItem::setBlockId(int blockId)
{
    _blockId = blockId;
    //判断规则里有木有；
    //findBlockItem();
}
int GroupItem::getMaxValue()
{
    return _max;
}
int GroupItem::getMinValue()
{
    return _min;

}
float GroupItem::getProbability()
{
    return _probability;
}
int GroupItem::getBlockId()
{
    return _blockId;
}
//GeneralBlock* GroupItem::findBlockItem()
//{
//    for(int i = 0; i < _blockRule.size(); i++)
//    {
//        if(_blockRule.at(i)->getBlockId() == _blockId)
//        {
//            _blockItem = _blockRule.at(i);
//            return _blockItem;
//        }
//    }
//    return NULL;

//}
QJsonObject GroupItem::exportJsonObject()
{
    QJsonObject object;
    object.insert("max",_max);
    object.insert("min",_min);
    object.insert("probability",_probability);
    object.insert("blockId",_blockId);
    return object;
}
GeneralBlock* GroupItem::getBlockItem()
{
    return _blockItem;
}
