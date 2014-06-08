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

class JsonHandle
{
public:

    BlockItemArray parserConfigJson(const char * fileDir);
    static JsonHandle* getInstance();
private:
    JsonHandle();
    BlockItemArray _blocksinfo;
    static JsonHandle* _ptr;

};

#endif // JSONHANDLE_H
