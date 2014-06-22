#ifndef JSONHANDLE_H
#define JSONHANDLE_H
#include <QString>
#include <QDebug>
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
#include <QMessageBox>
#include "../Block/generalBlock.h"
#include "../Block/commonBlock.h"
#include "../Block/colorBombBlock.h"
#include "../Block/petBlock.h"
#include <QObject>
#include "../Block/generalBlock.h"
#include "jsonprotocol.h"
#include "../DialogWidget/targetdata.h"
#include "../DialogWidget/createdata.h"
class JsonHandle
{
public:
    enum ConfigMode{
         ConfigFile,
         RuleFile
    };

    QVector<GeneralBlock*> parserConfigJson(const char * fileDir,ConfigMode mode);
    void parserRuleJson(const char * fileDir);
//    QJsonDocument exportJson(QVector<BlockLabel*> blockArray,
//                             QVector<DragLabel*> constraintArray,
//                             int row,int column,
//                             TargetData* target,
//                             QString background);
    QJsonDocument exportJson(JsonProtocol *data);
    JsonProtocol* importJson(const char* fileDir);

    QVector<BlockItem*> parserJsonFileForBlocks(const char * fileDir);
    QVector<DragLabel*> parserJsonFileForconstraint(const char* fileDir);
    CreateData* parserJsonFileForCreateData(const char * fileDir);
    TargetData* parserJsonFileForTargetData(const char * fileDir);
    QJsonArray parserJsonFileForGrouprule(const char *fileDir);

//    DataFormat* parserExistFile(const char* fileDir);
    static JsonHandle* getInstance();

private:
    JsonHandle();
   // void parserRuleByName(const char* fileName);
    int findBlockIds(QVector<GeneralBlock*> ruleBlocks,GeneralBlock* item);
    GeneralBlock* findGroupBlock(int blockId);
    QJsonParseError openJsonFile(const char* fileDir,QJsonDocument& document);
    void createGridIds();

    //BlockItemArray _blocksinfo;
    QVector<GeneralBlock*> _configBlocks;
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

    //DataFormat* fileContent;
    static JsonHandle* _ptr;

};

#endif // JSONHANDLE_H
