#include "jsonprotocol.h"

JsonProtocol::JsonProtocol()
{

}

void JsonProtocol::setCreateData(CreateData* createData)
{
    _createData = createData;
}
void JsonProtocol::setTarget(TargetData* target)
{
    _target = target;
}

void JsonProtocol::setBlocks(QVector<GeneralBlock*> blocks)
{
    _blocks = blocks;
}
CreateData* JsonProtocol::getCreateData()
{
    return _createData;
}
TargetData* JsonProtocol::getTargetData()
{
    return _target;
}
QVector<GeneralBlock*> JsonProtocol::getBlocks()
{
    return _blocks;
}

void JsonProtocol::setConstraints(QVector<DragLabel*> constraints)
{
   _constraints = constraints;
}

QVector<DragLabel*> JsonProtocol::getConstraints()
{
    return _constraints;
}
