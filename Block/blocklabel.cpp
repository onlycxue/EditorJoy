#include "blocklabel.h"

BlockLabel::BlockLabel(GeneralBlock *item,QWidget *parent):
    QLabel(parent)
{

    QPixmap pixmap(item->getResource());
    this->setScaledContents(true);
    this->setPixmap(pixmap);
    _propertys=item;
   // this->setMouseTracking(true);

}
BlockLabel::BlockLabel(QWidget *parent ):
    QLabel(parent),_focusColor(255,0,0)
{
    this->setMinimumSize(70,70);
    this->setMaximumSize(70,70);
    setStyleSheet("border-width: 1px; border-style: solid;border-color: transparent;");
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    propertyInit();
    _secondImgLabel = new QLabel(this);
    _secondImgLabel->setMaximumSize(70,70);
    _secondImgLabel->setMinimumSize(70,70);
    _thirdImagLabel = new QLabel(this);
    _thirdImagLabel->setMaximumSize(70,70);
    _thirdImagLabel->setMinimumSize(70,70);
//    propertyInit();
    QPixmap pixmap(BlueBlock);
    pixmap.scaled(70,70,Qt::KeepAspectRatio);
    this->setScaledContents(true);
    this->setPixmap(pixmap);

}

void BlockLabel::propertyInit()
{
      _propertys = new CommonBlock;
      CommonBlock* commonBlock = (CommonBlock*)_propertys;
      commonBlock->setPillarName("PRRuleCommonBlock");
      commonBlock->setFrozenable(false);
      commonBlock->setFrozenLevel(1);
      commonBlock->setResource("popup_7.png");
      commonBlock->setMatchType(0);
      commonBlock->setMultipliper(0);
      commonBlock->setType(0);
      commonBlock->setBlockId(-1);

}
void BlockLabel::setProperty(GeneralBlock* item)
{
    _propertys=item;

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
        setStyleSheet("border-width: 1px; border-style: solid;border-color: transparent;");
    }

}
GeneralBlock* BlockLabel::getPropertys()
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



