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
    _secondImgLabel = new QLabel(this);
    _secondImgLabel->setMaximumSize(70,70);
    _secondImgLabel->setMinimumSize(70,70);
    _thirdImagLabel = new QLabel(this);
    _thirdImagLabel->setMaximumSize(70,70);
    _thirdImagLabel->setMinimumSize(70,70);

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
    _propertys->_boxed = false;
    _propertys->_randomizedColor = -1;
    _propertys->_resource = "";

}
void BlockLabel::setProperty(BlockItem* item)
{
    _propertys->_pillar = item->_pillar;
    _propertys->_pillarName = item->_pillarName;
    _propertys->_frozen = item->_frozen;
    _propertys->_frozenLevel = item->_frozenLevel;
    _propertys->_matchType = item->_matchType;
    _propertys->_multiplier = item->_multiplier;
    _propertys->_type = item->_type;
    _propertys->_randomizedColor = item->_randomizedColor;
    _propertys->_colorbombmatchtype = item->_colorbombmatchtype;
    _propertys->_boxed = item->_boxed;
    _propertys->_resource = item->_resource;

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
void BlockLabel::setSecondImg(const char* fileName)
{
    QPixmap pixmap(fileName);
    pixmap.scaled(70,70,Qt::KeepAspectRatio);
    _secondImgLabel->setScaledContents(true);
    _secondImgLabel->setPixmap(pixmap);

}
void BlockLabel::setThirdImg(const char* fileName)
{
    QPixmap pixmap(fileName);
    pixmap.scaled(70,70,Qt::KeepAspectRatio);
    _thirdImagLabel->setScaledContents(true);
    _thirdImagLabel->setPixmap(pixmap);
}



