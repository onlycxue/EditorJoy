#ifndef JSONHANDLE_H
#define JSONHANDLE_H
#include <QString>
#include <qDebug>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include "../Global/globaldef.h"
#include <QVector>
#include "../Block/blockitem.h"
#include <QFile>
#include <QJsonObject>
#include <QVector>
#include "../Block/blocklabel.h"
#include "../Block/blockitem.h"

class JsonHandle
{
public:

    BlockItemArray parserConfigJson(const char * fileDir);
    void parserRuleJson(const char * fileDir);
    void exportJson(QVector<BlockLabel*> blockArray,int row,int column,const char *exportDir);
    static JsonHandle* getInstance();

private:
    JsonHandle();
   // void parserRuleByName(const char* fileName);
    void createBlockIds(QString name,BlockItem* item);
    BlockItemArray _blocksinfo;
    BlockItemArray _rules;
    //export
    QVector<int> _blockIds;
    QVector<int> _gridIds;

    QVector<BlockItem*> _PRRuleCommonBlocks;
    QVector<BlockItem*> _PRRulePetBlocks;
    QVector<BlockItem*> _otherBlocks;
    QVector<BlockItem*> _PRRuleColorBombBlocks;


    static JsonHandle* _ptr;

};

#endif // JSONHANDLE_H
