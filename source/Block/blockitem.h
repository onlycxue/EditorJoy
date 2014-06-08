#ifndef RULEITEM_H
#define RULEITEM_H

#include <QString>
#include <QVector>
class BlockItem
{
public:
    QString _pillar;
    QString _pillarName;
    int _frozenLevel;
    int _matchType;
    bool _frozen;
    int _randomizedColor;
    int _type;
    int _multiplier;
    QString _resource;


};

typedef QVector<BlockItem*> BlockItemArray;

#endif // RULEITEM_H
