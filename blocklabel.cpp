#include "blocklabel.h"

BlockLabel::BlockLabel(BlockItem *item,QWidget *parent):
    QLabel(parent),_propertys(item)
{
    //this->resize(70,70);
    qDebug() <<"resource : "<<_propertys->_resource << endl;
    QPixmap pixmap(item->_resource);
    this->setScaledContents(true);
    this->setPixmap(pixmap);
   // this->setMouseTracking(true);

}
BlockLabel::BlockLabel(QWidget *parent ):
    QLabel(parent),_focusColor(255,0,0)
{
    this->setMinimumSize(70,70);
    this->setMaximumSize(70,70);
    setStyleSheet("border-width: 1px; border-style: solid;border-color: rgb(255, 170, 0);");
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    propertyInit();
}

void BlockLabel::propertyInit()
{
    _propertys = new BlockItem;
    _propertys->_pillar = "";
    _propertys->_pillarName = "";
    _propertys->_frozen =false;
    _propertys->_frozenLevel = -1;
    _propertys->_matchType = -1;
    _propertys->_multiplier = -1;
    _propertys->_type = -1;
    _propertys->_randomizedColor = -1;
    _propertys->_resource = "";

}
void BlockLabel::setFocusColor(QColor color)
{
    _focusColor = color;

}

void BlockLabel::setSelect(bool flag)
{
    _isSelect = flag;
    if(flag)
    {
        setStyleSheet("border-width: 2px; border-style: solid;border-color: rgb(255, 0, 0);");
    }
    else
    {
        qDebug() << "clear"<<endl;
        setStyleSheet("border-width: 1px; border-style: solid;border-color: rgb(255, 170, 0);");
    }

}
BlockItem* BlockLabel::getPropertys()
{
    return _propertys;
}
bool BlockLabel::isSelect()
{
    return _isSelect;
}




