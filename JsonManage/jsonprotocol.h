#ifndef _JSONPROTOCOL_H_
#define _JSONPROTOCOL_H_

#include "../Block/generalBlock.h"
#include <QString>
#include <QVector>
#include "../OrnamentalWidget/draglabel.h"
#include "../DialogWidget/createdata.h"
#include "../DialogWidget/targetdata.h"


class JsonProtocol
{
public:
    JsonProtocol();
    void setCreateData(CreateData* createData);
    void setTarget(TargetData* target); 
    void setBlocks(QVector<GeneralBlock*> blocks);
    void setConstraints(QVector<DragLabel*> constraints);

    CreateData* getCreateData();
    TargetData* getTargetData();
    QVector<DragLabel*> getConstraints();
    QVector<GeneralBlock*> getBlocks();

private:
    TargetData* _target;
    CreateData* _createData;
    QVector<GeneralBlock*> _blocks;
    QVector<DragLabel*> _constraints;
};


#endif
