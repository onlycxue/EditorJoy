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

    virtual BlockBase& operator=(const BlockBase &other);
    virtual bool operator==(const BlockBase &other);

    QString getPillar();
    QString getPillarName();
    void setPillarName(QString name);
    void setPillar(QString name);
    void setType(int type);
    int getType();
    virtual QJsonObject exportJsonObject();
    virtual void printInfo();
 protected:
    QString _pillarName;
    QString _pillar;
    int _type;
};

#endif // RULEITEM_H
