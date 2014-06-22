#ifndef _GROUPDATA_H_
#define _GROUPDATA_H_
#include "groupitem.h"
#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class GroupData
{
public:
    GroupData();
    GroupData(QJsonObject obj);
    void setName(QString name);
    void setGroupId(int id);
    QString getName();
    int getGroupId();
    QVector<GroupItem*> getGroupItems();
    void insertJsonObject(QJsonObject &obj);
    void groupItemsInit(QJsonArray array);
    void addGroupItem(GroupItem* item);
    void removeGroupitem(int i);
    //QVector<GeneralBlock*> getGroupBlockRules();
private:
    QString _name;
    int _groupId;
    QVector<GroupItem*> _groupItems;
    //QVector<GeneralBlock*> _groupBlockRules;
};


#endif
