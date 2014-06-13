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
#include "../DialogWidget/targetdialog.h"

typedef struct
{
    int _rows;
    int _column;
//    TargetData* _target;
    QVector<BlockItem*> _blocks;
    QVector<DragLabel*> _constraints;

}DataFormat;

class JsonHandle
{
public:

    BlockItemArray parserConfigJson(const char * fileDir);
    void parserRuleJson(const char * fileDir);
    QJsonDocument exportJson(QVector<BlockLabel*> blockArray,
                             QVector<DragLabel*> constraintArray,
                             int row,int column,
                             TargetData* target,
                             QString background);
    QVector<BlockItem*> parserJsonFileForBlocks(const char * fileDir);
    QVector<DragLabel*> parserJsonFileForconstraint(const char* fileDir);

    DataFormat* parserExistFile(const char* fileDir);
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

    int _rows;
    int _column;

    DataFormat* fileContent;
    static JsonHandle* _ptr;

};

#endif // JSONHANDLE_H
