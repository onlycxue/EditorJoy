#ifndef RULEITEM_H
#define RULEITEM_H

#include <QString>
#include <QVector>
#include <QDebug>

class BlockItem
{
public:
    QString _pillar;
    QString _pillarName;
    int _frozenLevel;
    int _matchType;
    bool _frozen;
    bool _randomizedColor;
    int _type;
    int _multiplier;
    int _blockId;
    int _colorbombmatchtype;
    bool _boxed;
    QString _rulename;

    QString _resource;
    void init()
    {
        _pillar = QString("");
        _pillarName = QString("");
        _frozenLevel = 1;
        _matchType = 0;
        _frozen = false;
        _randomizedColor = false;
        _colorbombmatchtype = 0;
        _boxed = false;
        _type = -1;
        _multiplier = 0;
        _blockId = -1;
        _resource = QString("");
    }
    void printInfo()
    {
        qDebug()<<"pillar: " << _pillar ;
        qDebug()<<"pillarName: " << _pillarName ;
        qDebug()<<"frozenLevel: " <<_frozenLevel ;
        qDebug()<<"matchType: " << _matchType ;
        qDebug()<<"frozen: " << _frozen;
        qDebug()<<"randomizedColor: " <<_randomizedColor ;
        qDebug() << "colorbombmatchtype:" << _colorbombmatchtype;
        qDebug()<<"type: " << _type;
        qDebug()<<"multiplier: " << _multiplier;
        qDebug()<< "blockId: " << _blockId;
        //qDebug()<<"frozenLevel: " <<_frozenLevel << endl;
    }

};

typedef QVector<BlockItem*> BlockItemArray;

#endif // RULEITEM_H
