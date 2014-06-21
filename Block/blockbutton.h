#ifndef BLOCKBUTTON_H
#define BLOCKBUTTON_H
#include <QPushButton>
#include "blockitem.h"
#include <QDebug>
#include "generalBlock.h"

class BlockButton : public QPushButton
{
     Q_OBJECT
public:
    BlockButton(GeneralBlock *item,QWidget* parent = 0);
    void mousePressEvent(QMouseEvent *event);

signals:
    void Click(GeneralBlock*);
private:
    GeneralBlock* _propertys;
};

#endif // BLOCKBUTTON_H
