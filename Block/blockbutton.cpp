#include "blockbutton.h"

BlockButton::BlockButton(BlockItem *item,QWidget* parent):
    QPushButton(parent),_propertys(item)
{
    this->setMinimumSize(QSize(70,70));
    setIconSize(QSize(70,70));
    setIcon(QIcon(item->_resource));
    //this->setFlat(true);
    //qDebug() << "#######blockButton#######" << _propertys->_type<< endl;
}

void BlockButton::mousePressEvent(QMouseEvent *event)
{
    //把当前blocked的属性发送给编辑widget.
    emit Click(_propertys);
}
