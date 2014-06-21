#include "groupdata.h"

GroupData::GroupData()
{

}
GroupData::GroupData(QJsonObject obj)
{
    _name = obj.take("name").toString();
    _groupId = obj.take("groupId").toInt();

    groupItemsInit(obj.take("pillars").toArray());

}
void GroupData::setName(QString name)
{
    _name = name;
}
void GroupData::setGroupId(int id)
{
    _groupId = id;
}
QString GroupData::getName()
{
    return _name;
}
int GroupData::getGroupId()
{
    return _groupId;
}
void GroupData::addGroupItem(GroupItem* item)
{
    _groupItems.append(item);
}
QVector<GroupItem*> GroupData::getGroupItems()
{
    return _groupItems;
}
void GroupData::insertJsonObject(QJsonObject &obj)
{
    obj.insert("name",_name);
    obj.insert("groupId",_groupId);
    QJsonArray items;
    for(int i = 0 ; i < _groupItems.size();i++)
    {
        items.insert(i,_groupItems.at(i)->exportJsonObject());
    }
    obj.insert("pillars",items);
}

void GroupData::groupItemsInit(QJsonArray array)
{
    for(int i = 0 ; i < array.size(); i++)
    {
        QJsonObject obj = array.at(i).toObject();
        _groupItems.append(new GroupItem(obj));
    }
}
void GroupData::removeGroupitem(int i)
{
    _groupItems.removeAt(i);
}

