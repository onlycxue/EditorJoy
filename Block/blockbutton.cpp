#include "blockbutton.h"

BlockButton::BlockButton(GeneralBlock *item,QWidget* parent):
    QPushButton(parent),_propertys(item)
{
    this->setMinimumSize(QSize(70,70));
    setIconSize(QSize(70,70));
    setIcon(QIcon(item->getResource()));
}

void BlockButton::mousePressEvent(QMouseEvent *event)
{
    //把当前blocked的属性发送给编辑widget.
    emit Click(_propertys);
}
