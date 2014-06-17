#ifndef _BLOCKBase_H_
#define _BLOCKBase_H_

#include <QString>
#include <QVector>
#include <QDebug>
#include <QJsonObject>

class BlockBase
{
public:
    BlockBase();
    BlockBase(BlockBase &block);

    BlockBase& operator=(const BlockBase &other);
    bool operator==(const BlockBase &other);

    QString getPillar();
    QString getPillarName();
    void setType(int type);
    int getType();
    virtual QJsonObject exportJsonObject();
 protected:
    QString _pillarName;
    QString _pillar;
    int _type;
};

#endif // RULEITEM_H
