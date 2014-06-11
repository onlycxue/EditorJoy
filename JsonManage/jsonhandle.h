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
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include "../OrnamentalWidget/draglabel.h"

class JsonHandle
{
public:

    BlockItemArray parserConfigJson(const char * fileDir);
    void parserRuleJson(const char * fileDir);
    QJsonDocument exportJson(QVector<BlockLabel*> blockArray,
                             QVector<DragLabel*> constraintArray,
                             int row,int column,
                             const char *exportDir);
    QVector<BlockItem*> parserJsonFileForBlocks(const char * fileDir);
    QVector<DragLabel*> parserJsonFileForconstraint(const char* fileDir,QWidget* parent);

    static JsonHandle* getInstance();

private:
    JsonHandle();
   // void parserRuleByName(const char* fileName);
    void createBlockIds(QString name,BlockItem* item);
    void createGridIds();

    BlockItemArray _blocksinfo;
    BlockItemArray _rules;
    //export
    QVector<int> _blockIds;
    QVector<int> _gridIds;

    //import
    QVector<DragLabel*> _constraints;

    QVector<BlockItem*> _PRRuleCommonBlocks;
    QVector<BlockItem*> _PRRulePetBlocks;
    QVector<BlockItem*> _otherBlocks;
    QVector<BlockItem*> _PRRuleColorBombBlocks;
    QVector<BlockItem*> _exportBlocksRule;


    static JsonHandle* _ptr;

};

#endif // JSONHANDLE_H
