#ifndef BLOCKBUTTON_H
#define BLOCKBUTTON_H
#include <QPushButton>
#include "blockitem.h"

class BlockButton : public QPushButton
{
     Q_OBJECT
public:
    BlockButton(BlockItem *item,QWidget* parent = 0);
    void mousePressEvent(QMouseEvent *event);

signals:
    void Click(BlockItem*);
private:
    BlockItem* _propertys;
};

#endif // BLOCKBUTTON_H
