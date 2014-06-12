#include "editorwidget.h"

EditorWidget::EditorWidget(DataFormat* data):_row(data->_rows),_column(data->_column),
    _dragLabels(data->_constraints),_touchingLabel(NULL),_selectedNum(-1)
{
    editWidgetInit();
    blocksInit();
    this->setMouseTracking(true);
    actionInit();
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    for(int i = 0 ; i <data->_blocks.size();i++)
    {
        _blocks.at(i)->setProperty(data->_blocks.at(i));
        setBlocksStatus(_blocks.at(i));
    }
    for(int i = 0 ; i < _dragLabels.size(); i++)
    {
        _dragLabels.at(i)->setParent(this);
        connect(_dragLabels.at(i),SIGNAL(sendTouchingLabel(DragLabel*)),this,SLOT(touchingLabel(DragLabel*)));
        connect(_dragLabels.at(i),SIGNAL(sendTouchEnd()),this,SLOT(touchingClean()));
        connect(_dragLabels.at(i),SIGNAL(sendDeleteLabel(DragLabel*)),this,SLOT(deleteDragLabel(DragLabel*)));

    }

}
EditorWidget::EditorWidget(int row,int column):
                      _row(row),_column(column),_selectedNum(-1),_touchingLabel(NULL)
{

    editWidgetInit();
    blocksInit();
    this->setMouseTracking(true);
    actionInit();
    this->setContextMenuPolicy(Qt::DefaultContextMenu);

}
void EditorWidget::editWidgetInit()
{
    _blocksBoard = new QWidget(this);
    _blocksBoard->setAttribute(Qt::WA_TransparentForMouseEvents);
    _gridLayout = new QGridLayout(_blocksBoard);
    //设置编辑区的背景颜色
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    setPalette(palette);
    _blocksBoard->resize(BLOCK_WIDTH*(_column+0.2),BLOCK_HEIGHT*(_row+0.2));
    this->resize(640,800);
    int x =(width()-BLOCK_WIDTH*(_column+0.2))/2;
    int y =(height() - BLOCK_HEIGHT*(_row+0.2))/2;
    _blocksBoard->setGeometry(x,y,_blocksBoard->width(),_blocksBoard->height());
}
void EditorWidget::blocksInit()
{

    for(int i = 0 ; i < _row ; i++)
    {
        for(int j = 0; j < _column ; j++)
        {
            qDebug() << "position is " << _row << _column << endl;
            BlockLabel* block = new BlockLabel(_blocksBoard);
            //block->installEventFilter(this);
            block->setAttribute(Qt::WA_TransparentForMouseEvents);
            QString rowStr;
            QString columnStr;
            rowStr.setNum(i);
            columnStr.setNum(j);
            //block->setText("( "+rowStr+","+ columnStr + " )");
            block->setText("( "+columnStr+","+ rowStr + " )");
            block->setAlignment(Qt::AlignCenter);
            //添加到容器
            _blocks.append(block);
            _gridLayout->addWidget(block,i,j);
        }
    }
}
void EditorWidget::setRow(int num)
{
    _row = num;
}
void EditorWidget::setColumn(int num)
{
    _column = num;
}
float EditorWidget::getMouseX()
{
    if(_touchingLabel == NULL)
        return _mouseX;
    else
        return _touchingLabel->x();
}
float EditorWidget::getMouseY()
{
    if(_touchingLabel == NULL)
        return _mouseY;
    else
        return _touchingLabel->y();

}
void EditorWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->x() >= _blocksBoard->x()+_blocksBoard->width() ||
          event->y() >= _blocksBoard->y()+_blocksBoard->height() ||
            event->y() <= _blocksBoard->y() || event->x() <= _blocksBoard->x())
    {
        return;
    }
    int num = (event->x()-_blocksBoard->x())/BLOCK_WIDTH + (event->y()-_blocksBoard->y())/BLOCK_HEIGHT*_column;
    //qDebug() << (event->x()-_blocksBoard->x())/BLOCK_WIDTH<< "###" << (event->y()-_blocksBoard->y())/BLOCK_HEIGHT <<endl;
    qDebug() << "Select Num:" << num;
    qDebug() << "_blocks Size:" << _blocks.size();
    if(_selectedNum != num && num < _column*_row)
    {

        if(_selectedNum != -1)
        {
           _blocks.at(_selectedNum)->setSelect(false);
        }
        _selectedNum = num;
        _blocks.at(_selectedNum)->setSelect(true);
    }


}

void EditorWidget::mouseMoveEvent(QMouseEvent *event)
{
//     qDebug() << event->x()<< "@@@" << event->y()<<endl;
     _mouseX = event->x();
     _mouseY = event->y();

}

void EditorWidget::msgHandler(BlockItem* item)
{
    //要判断一下type是否为-1
    QPixmap pixmap(item->_resource);
    if(_selectedNum != -1)
    {
        int width = _blocks.at(_selectedNum)->width();
        int height = _blocks.at(_selectedNum)->height();

        pixmap.scaled(width,height,Qt::KeepAspectRatio);
        _blocks.at(_selectedNum)->setScaledContents(true);

        _blocks.at(_selectedNum)->setPixmap(pixmap);
        _blocks.at(_selectedNum)->setProperty(item);
        qDebug() << "####msgHandle####" << _blocks.at(_selectedNum)->getPropertys()->_type << "##########";
        qDebug() << "####msgHandle####" << item->_frozen << "##########";
    }
    }

void EditorWidget::addDragLabel(QListWidgetItem* item)
{

    //添加装饰物到widgetBlocks
    DragLabel * label = new DragLabel(this);
    //label->setAttribute(Qt::WA_TransparentForMouseEvents);
    label->show();
    char chImageDir[200];
    sprintf(chImageDir,"%s/%s",ConstraintsBasePath,item->text().toUtf8().data());

    label->m_strImageName = item->text().toUtf8().data();
    QPixmap pixMap(chImageDir);
    label->setPixmap(pixMap);
    label->setGeometry(this->width()/2,this->height()/2,pixMap.width(),pixMap.height());
    connect(label,SIGNAL(sendTouchingLabel(DragLabel*)),this,SLOT(touchingLabel(DragLabel*)));
    connect(label,SIGNAL(sendTouchEnd()),this,SLOT(touchingClean()));
    connect(label,SIGNAL(sendDeleteLabel(DragLabel*)),this,SLOT(deleteDragLabel(DragLabel*)));
    _dragLabels.append(label);

}

void EditorWidget::actionInit()
{
    _colorGroup = new QActionGroup(this);
    _boxedGroup = new QActionGroup(this);

    _blueColor = new QAction(tr("blue"),this);
    _blueColor->setCheckable(true);
    //_blueColor->setChecked(true);
    _colorGroup->addAction(_blueColor);
    _boxedGroup->addAction(_blueColor);
    connect(_blueColor,SIGNAL(triggered()),this,SLOT(setBlueBlock()));

    _yellowColor = new QAction(tr("yellow"),this);
    _yellowColor->setCheckable(true);
    //_yellowColor->setChecked(true);
    _colorGroup->addAction(_yellowColor);
    _boxedGroup->addAction(_yellowColor);

    connect(_yellowColor,SIGNAL(triggered()),this,SLOT(setYellowBlock()));

    _redColor = new QAction(tr("red"),this);
    _redColor->setCheckable(true);
   // _redColor->setChecked(true);
    _colorGroup->addAction(_redColor);
    _boxedGroup->addAction(_redColor);
    connect(_redColor,SIGNAL(triggered()),this,SLOT(setRedBlock()));

    _pinkColor = new QAction(tr("pink"),this);
    _pinkColor->setCheckable(true);
   // _pinkColor->setChecked(true);
    _colorGroup->addAction(_pinkColor);
    _boxedGroup->addAction(_pinkColor);
    connect(_pinkColor,SIGNAL(triggered()),this,SLOT(setPurpleBlock()));

    _greenColor = new QAction(tr("green"),this);
    _greenColor->setCheckable(true);
   // _greenColor->setChecked(true);
    _colorGroup->addAction(_greenColor);
    _boxedGroup->addAction(_greenColor);
    connect(_greenColor,SIGNAL(triggered()),this,SLOT(setGreenBlock()));

    _noBox = new QAction(tr("noBox"),this);
    _boxedGroup->addAction(_noBox);
    _noBox->setCheckable(true);
    connect(_noBox,SIGNAL(triggered()),this,SLOT(setNoBox()));


    _frozenGroup = new QActionGroup(this);

    _frozen0 = new QAction(tr("no"),this);
    _frozen0->setCheckable(true);
    _frozen0->setChecked(true);
    connect(_frozen0,SIGNAL(triggered()),this,SLOT(setFrozen0()));
    _frozenGroup->addAction(_frozen0);

    _frozen1 = new QAction(tr("level1"),this);
    _frozen1->setCheckable(true);
    connect(_frozen1,SIGNAL(triggered()),this,SLOT(setFrozen1()));
    _frozenGroup->addAction(_frozen1);

    _frozen2 = new QAction(tr("level2"),this);
    _frozen2->setCheckable(true);
    connect(_frozen2,SIGNAL(triggered()),this,SLOT(setFrozen2()));

    _frozenGroup->addAction(_frozen2);

    _multiplier = new QAction(tr("multiplier"),this);
    _multiplier->setCheckable(true);
    connect(_multiplier,SIGNAL(triggered()),this,SLOT(setmultiply()));
    _addGroup = new QAction(tr("addGroup"),this);

}
void EditorWidget::contextMenuEvent(QContextMenuEvent *event)
{
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    if(type == -1)
        return;

     _mainMenu = new QMenu(this);
    setActionStatus();
    _mainMenu->addAction(_addGroup);
    _mainMenu->exec(event->globalPos());

}
//用来处理QAction
void EditorWidget::changeBlockResource(const char* file,BlockLabel* item)
{
    QPixmap pixmap(file);
    int width = item->width();
    int height = item->height();
    pixmap.scaled(width,height,Qt::KeepAspectRatio);
    item->setScaledContents(true);
    item->setPixmap(pixmap);

}
void EditorWidget::setBlueBlock()
{
    if(_selectedNum != -1)
    {
        int type = _blocks.at(_selectedNum)->getPropertys()->_type;
        qDebug() << "########" << type << "##########";
        if(0 <= type&&type<=4)
        {
            changeBlockResource(BlueBlock,_blocks.at(_selectedNum));
             _blocks.at(_selectedNum)->getPropertys()->_type = 0;
        }
        else if(7 <= type && type <=11)
        {
            changeBlockResource(BlueColorBomb,_blocks.at(_selectedNum));
            //_blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
            _blocks.at(_selectedNum)->getPropertys()->_type = 7;
            _blocks.at(_selectedNum)->getPropertys()->_colorbombmatchtype = BLUE;
        }
        else if(type == 999)
        {
           // changeBlockResource(BlueCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
            _blocks.at(_selectedNum)->getPropertys()->_boxed = true;
            _blocks.at(_selectedNum)->setSecondImg(BlueCarrier);
        }
    }
}
void EditorWidget::setYellowBlock()
{
    if(_selectedNum != -1)
    {
        int type = _blocks.at(_selectedNum)->getPropertys()->_type;
        if(0 <= type&&type<=4)
        {

            changeBlockResource(YellowBlock,_blocks.at(_selectedNum));
             _blocks.at(_selectedNum)->getPropertys()->_type = 1;
             _blocks.at(_selectedNum)->getPropertys()->_matchType = 1;
        }
        else if(7 <= type && type <=11)
        {
            changeBlockResource(YellowColorBomb,_blocks.at(_selectedNum));
            //_blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
            _blocks.at(_selectedNum)->getPropertys()->_type = 8;
            _blocks.at(_selectedNum)->getPropertys()->_colorbombmatchtype = YELLOW;
        }
        else if(type == 999)
        {
            //changeBlockResource(YellowCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 1;
            _blocks.at(_selectedNum)->setSecondImg(YellowCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_boxed = true;
        }
    }

}
void EditorWidget::setRedBlock()
{
    if(_selectedNum != -1)
    {
        int type = _blocks.at(_selectedNum)->getPropertys()->_type;
        if(0 <= type&&type<=4)
        {
             _blocks.at(_selectedNum)->getPropertys()->_type = 2;
             _blocks.at(_selectedNum)->getPropertys()->_matchType = 2;
             changeBlockResource(RedBlock,_blocks.at(_selectedNum));
        }
        else if(7 <= type && type <=11)
        {
            changeBlockResource(RedColorBomb,_blocks.at(_selectedNum));
            //_blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
            _blocks.at(_selectedNum)->getPropertys()->_type = 9;
            _blocks.at(_selectedNum)->getPropertys()->_colorbombmatchtype = RED;
        }
        else if(type == 999)
        {
            //changeBlockResource(RedCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 2;
            _blocks.at(_selectedNum)->setSecondImg(RedCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_boxed = true;
        }
    }

}
void EditorWidget::setGreenBlock()
{
    if(_selectedNum != -1)
    {
        int type = _blocks.at(_selectedNum)->getPropertys()->_type;
        if(0 <= type&&type<=4)
        {
             _blocks.at(_selectedNum)->getPropertys()->_type = 3;
             _blocks.at(_selectedNum)->getPropertys()->_matchType = 3;
             changeBlockResource(GreenBlock,_blocks.at(_selectedNum));
        }
        else if(7 <= type && type <=11)
        {
            changeBlockResource(GreenColorBomb,_blocks.at(_selectedNum));
            //_blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
            _blocks.at(_selectedNum)->getPropertys()->_type = 10;
            _blocks.at(_selectedNum)->getPropertys()->_colorbombmatchtype = GREEN;
        }
        else if(type == 999)
        {
            //changeBlockResource(GreenCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 3;
            _blocks.at(_selectedNum)->setSecondImg(GreenCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_boxed = true;
        }
    }
}
void EditorWidget::setPurpleBlock()
{
    if(_selectedNum != -1)
    {
        int type = _blocks.at(_selectedNum)->getPropertys()->_type;
        if(0 <= type&&type<=4)
        {
             _blocks.at(_selectedNum)->getPropertys()->_type = 4;
             _blocks.at(_selectedNum)->getPropertys()->_matchType = 4;
             changeBlockResource(PurpleBlock,_blocks.at(_selectedNum));
        }
        else if(7 <= type && type <=11)
        {
            changeBlockResource(PurpleColorBomb,_blocks.at(_selectedNum));
            //_blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
            _blocks.at(_selectedNum)->getPropertys()->_type = 11;
            _blocks.at(_selectedNum)->getPropertys()->_colorbombmatchtype = PURPLE;
        }
        else if(type == 999)
        {
            //changeBlockResource(PurpleCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 4;
            _blocks.at(_selectedNum)->setSecondImg(PurpleCarrier);
            _blocks.at(_selectedNum)->getPropertys()->_boxed = true;
        }
    }

}
void EditorWidget::setFrozen0()
{
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    if(0 <= type&&type<=4)
    {
         _blocks.at(_selectedNum)->getPropertys()->_frozenLevel = 0;
         _blocks.at(_selectedNum)->getPropertys()->_frozen = false;
         _blocks.at(_selectedNum)->setSecondImg("");
         _blocks.at(_selectedNum)->setThirdImg("");
    }
}
void EditorWidget::setFrozen1()
{
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    if(0 <= type&&type<=4)
    {
         _blocks.at(_selectedNum)->getPropertys()->_frozenLevel = 1;
         _blocks.at(_selectedNum)->getPropertys()->_frozen = true;
         _blocks.at(_selectedNum)->setSecondImg(FrozenLevel1);
         _blocks.at(_selectedNum)->setThirdImg("");
    }
}
void EditorWidget::setFrozen2()
{
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    if(0 <= type&&type<=4)
    {
         _blocks.at(_selectedNum)->getPropertys()->_frozenLevel = 2;
         _blocks.at(_selectedNum)->getPropertys()->_frozen = true;
         _blocks.at(_selectedNum)->setSecondImg(FrozenLevel1);
         _blocks.at(_selectedNum)->setThirdImg(FrozenLevel2);
    }
}
void EditorWidget::setmultiply()
{
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    int multiply = _blocks.at(_selectedNum)->getPropertys()->_multiplier;
    if(0 <= type&&type<=4)
    {
        if(multiply == 0)
        {
             _blocks.at(_selectedNum)->getPropertys()->_multiplier = 2;
             _blocks.at(_selectedNum)->setSecondImg(MultiplyFlag);
        }
        else
        {
            _blocks.at(_selectedNum)->getPropertys()->_multiplier = 0;
            _blocks.at(_selectedNum)->setSecondImg("");
        }
    }
}

void EditorWidget::setNoBox()
{
    _blocks.at(_selectedNum)->getPropertys()->_boxed = false;
    _blocks.at(_selectedNum)->setSecondImg("");
}

void EditorWidget::setColorActionStatus(int type)
{
    _colorMenu = _mainMenu->addMenu("color");
    _colorMenu->addAction(_blueColor);
    _colorMenu->addAction(_yellowColor);
    _colorMenu->addAction(_redColor);
    _colorMenu->addAction(_pinkColor);
    _colorMenu->addAction(_greenColor);

    switch(type)
    {
        case -1:
                _colorMenu->setEnabled(false);
                break;
        case 0:
                _blueColor->setChecked(true);
                _yellowColor->setChecked(false);
                _redColor->setChecked(false);
                _pinkColor->setChecked(false);
                _greenColor->setChecked(false);
                break;
       case 1:
                _blueColor->setChecked(false);
                _yellowColor->setChecked(true);
                _redColor->setChecked(false);
                _pinkColor->setChecked(false);
                _greenColor->setChecked(false);
                break;
       case 2 :
                _blueColor->setChecked(false);
                _yellowColor->setChecked(false);
                _redColor->setChecked(true);
                _pinkColor->setChecked(false);
                _greenColor->setChecked(false);
                break;
       case 3 :
                 _blueColor->setChecked(false);
                 _yellowColor->setChecked(false);
                 _redColor->setChecked(false);
                 _pinkColor->setChecked(false);
                 _greenColor->setChecked(true);
                 break;
       case 4 :
                _blueColor->setChecked(false);
                _yellowColor->setChecked(false);
                _redColor->setChecked(false);
                _pinkColor->setChecked(true);
                _greenColor->setChecked(false);
                break;

       default:
                break;
    }

}
void EditorWidget::setBoxColorActionStatus(int type,bool flag)
{
    _boxedMenu = _mainMenu->addMenu("box");
    _boxedMenu->addAction(_blueColor);
    _boxedMenu->addAction(_yellowColor);
    _boxedMenu->addAction(_redColor);
    _boxedMenu->addAction(_pinkColor);
    _boxedMenu->addAction(_greenColor);
    _boxedMenu->addAction(_noBox);

    if(!flag)
    {
        _blueColor->setChecked(false);
        _yellowColor->setChecked(false);
        _redColor->setChecked(false);
        _pinkColor->setChecked(false);
        _greenColor->setChecked(false);
        _noBox->setChecked(true);
        return;
    }

    switch(type)
    {
        case -1:
                _colorMenu->setEnabled(false);
                break;
        case 0:
                _blueColor->setChecked(true);
                _yellowColor->setChecked(false);
                _redColor->setChecked(false);
                _pinkColor->setChecked(false);
                _greenColor->setChecked(false);
                _noBox->setChecked(false);
                break;
       case 1:
                _blueColor->setChecked(false);
                _yellowColor->setChecked(true);
                _redColor->setChecked(false);
                _pinkColor->setChecked(false);
                _greenColor->setChecked(false);
                _noBox->setChecked(false);
                break;
       case 2 :
                _blueColor->setChecked(false);
                _yellowColor->setChecked(false);
                _redColor->setChecked(true);
                _pinkColor->setChecked(false);
                _greenColor->setChecked(false);
                _noBox->setChecked(false);
                break;
       case 3 :
                 _blueColor->setChecked(false);
                 _yellowColor->setChecked(false);
                 _redColor->setChecked(false);
                 _pinkColor->setChecked(false);
                 _greenColor->setChecked(true);
                 _noBox->setChecked(false);
                 break;
       case 4 :
                _blueColor->setChecked(false);
                _yellowColor->setChecked(false);
                _redColor->setChecked(false);
                _pinkColor->setChecked(true);
                _greenColor->setChecked(false);
                _noBox->setChecked(false);
                break;

       default:
                break;
    }
}

void EditorWidget::setForzenStatus(int level)
{
    _frozenMenu = _mainMenu->addMenu("frozen");
    _frozenMenu->addAction(_frozen1);
    _frozenMenu->addAction(_frozen2);
    _frozenMenu->addAction(_frozen0);

    switch(level)
    {
    //FrozenLevel1
        case -1:
                //_frozenMenu->setEnabled(false);
                _frozenMenu->setVisible(false);
                break;
        case 0:
                //_blocks.at(_selectedNum)->setSecondImg("");
                //_blocks.at(_selectedNum)->setThirdImg("");
                _frozen0->setChecked(true);
                _frozen1->setChecked(false);
                _frozen2->setChecked(false);
                break;
        case 1:
               //_blocks.at(_selectedNum)->setSecondImg(FrozenLevel1);
               _frozen0->setChecked(false);
               _frozen1->setChecked(true);
               _frozen2->setChecked(false);
               break;
        case 2:
               //_blocks.at(_selectedNum)->setThirdImg(FrozenLevel2);
               _frozen0->setChecked(false);
               _frozen1->setChecked(false);
               _frozen2->setChecked(true);
               break;
        default:
               break;
    }
}
void EditorWidget::setmultiplyStatus(int level)
{
    _mainMenu->addAction(_multiplier);
    _multiplier->setChecked(false);
    qDebug() << "########setmultiplyStatus#######"<< level;
    switch(level)
    {
        case -1:
            _multiplier->setDisabled(true);
            break;
        case 0:
//            _blocks.at(_selectedNum)->setSecondImg("");
//            _blocks.at(_selectedNum)->setThirdImg("");
            _multiplier->setChecked(false);
            break;
        case 1:
//            _blocks.at(_selectedNum)->setSecondImg(MultiplyFlag);
            _multiplier->setChecked(true);
            break;
        default:
            break;

    }
}
void EditorWidget::setActionStatus()
{
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    int frozenLevel = _blocks.at(_selectedNum)->getPropertys()->_frozenLevel;
    int multiPly = _blocks.at(_selectedNum)->getPropertys()->_multiplier;
     qDebug() << "###frozenLevel###" << frozenLevel;
    if( 0 <= type && type <=4)
    {
        setColorActionStatus(type);
        setForzenStatus(frozenLevel);
        setmultiplyStatus(multiPly);
    }
    else if (7 <= type && type <= 11)
    {
        int matchType = _blocks.at(_selectedNum)->getPropertys()->_colorbombmatchtype;
        setColorActionStatus(matchType);
    }
    else if(type == 999)
    {
        int matchType =  _blocks.at(_selectedNum)->getPropertys()->_matchType;
        bool boxedFlag = _blocks.at(_selectedNum)->getPropertys()->_boxed;
        qDebug() << "boxed flag is " << boxedFlag;
        setBoxColorActionStatus(matchType,boxedFlag);
    }

}
QString EditorWidget::getResourceFromConfig(QString name)
{
   qDebug() << "current name is " << name;
  BlockItemArray array = JsonHandle::getInstance()->parserConfigJson(BlockConfigPath);
  for(int i = 0 ; i < array.size(); i++)
  {
        qDebug() << "{" ;
        array.at(i)->printInfo();
        qDebug() << "}";
        if(name.compare(array.at(i)->_pillarName) == 0)
        {
            return array.at(i)->_resource;
        }
  }
  return QString::null;
}
void EditorWidget::setBlocksStatus(BlockLabel* item)
{
    if(item->getPropertys()->_pillarName.compare("PRRuleCommonBlock")==0)
    {
        int frozenLevel = item->getPropertys()->_frozenLevel;
        int multiplyFlag = item->getPropertys()->_multiplier;
        bool frozen = item->getPropertys()->_frozen;
        setBlockColor(item);
        if(frozen)
        {
            if(frozenLevel == 1)
            {
                item->setSecondImg(FrozenLevel1);
            }
            else if(frozenLevel == 2)
            {
                item->setSecondImg(FrozenLevel1);
                item->setThirdImg(FrozenLevel2);
            }
        }
        if(multiplyFlag == 2)
        {
            item->setSecondImg(MultiplyFlag);
        }

    }
    else if(item->getPropertys()->_pillarName.compare("PRRuleColorBombBlock") == 0)
    {
        setBlockColor(item);
    }
    else if(item->getPropertys()->_pillarName.compare("PRRulePetBlock") == 0)
    {
        if(item->getPropertys()->_boxed)
        {
            setPetBoxedColor(item);
        }
        else
        {
            QString imageName = EditorWidget::getResourceFromConfig(item->getPropertys()->_pillarName);
            changeBlockResource(imageName.toUtf8().data(),item);
        }
    }
    else
    {

        QString imageName = EditorWidget::getResourceFromConfig(item->getPropertys()->_pillarName);
        changeBlockResource(imageName.toUtf8().data(),item);

    }
}
void EditorWidget::setBlockColor(BlockLabel*  item)
{
    switch(item->getPropertys()->_type)
    {
        case 0:
               changeBlockResource(BlueBlock,item);
               break;
        case 1:
               changeBlockResource(YellowBlock,item);
               break;
        case 2:
               changeBlockResource(RedBlock,item);
               break;
        case 3:
               changeBlockResource(GreenBlock,item);
               break;
        case 4:
               changeBlockResource(PurpleBlock,item);
               break;
        case 7:
               changeBlockResource(BlueColorBomb,item);
               break;
        case 8:
               changeBlockResource(YellowColorBomb,item);
               break;
        case 9:
               changeBlockResource(RedColorBomb,item);
               break;
        case 10:
               changeBlockResource(GreenColorBomb,item);
               break;
        case 11:
               changeBlockResource(PurpleColorBomb,item);
               break;
        default :
               break;

    }
}
void EditorWidget::setPetBoxedColor(BlockLabel*  item)
{
    switch(item->getPropertys()->_matchType)
    {
        case 0:
               changeBlockResource(BlueCarrier,item);
               break;
        case 1:
               changeBlockResource(YellowCarrier,item);
               break;
        case 2:
               changeBlockResource(RedCarrier,item);
               break;
        case 3:
               changeBlockResource(GreenCarrier,item);
               break;
        case 4:
               changeBlockResource(PurpleCarrier,item);
               break;
        default:
               break;
    }
}
void EditorWidget::exportBlocksMsg()
{
    qDebug() << "############exportMsg#############" << endl;
    for(int i = 0;i < _blocks.size(); i++)
    {
        qDebug()<<"{" <<endl;
        _blocks.at(i)->getPropertys()->printInfo();
        qDebug()<<"}" <<endl;
    }
}
void EditorWidget::deleteDragLabel(DragLabel* item)
{
    int index = _dragLabels.indexOf(item);
    qDebug() << "#####################delete###############"<< index;
    _dragLabels.removeAt(index);
    qDebug() << "#####################size:###############"<< _dragLabels.size();

    //delete item;
}
int EditorWidget::getRow()
{
    return _row;
}
int EditorWidget::getColumn()
{
    return _column;
}
QVector<BlockLabel*> EditorWidget::getBlocks()
{
    return _blocks;
}
QVector<DragLabel*> EditorWidget::getConstraints()
{
    return _dragLabels;
}
void EditorWidget::touchingLabel(DragLabel* label)
{
    _touchingLabel = label;
}
void EditorWidget::touchingClean()
{
    _touchingLabel = NULL;
}
EditorWidget::~EditorWidget()
{
//    delete _mainMenu;
//    delete _colorMenu;
//    delete _frozenMenu;
//    delete _boxedMenu;

//    //二级菜单颜色

//    delete _colorGroup;
//    delete _blueColor;
//    delete _yellowColor;
//    delete _redColor;
//    delete _pinkColor;
//    delete _greenColor;


//    //铁笼等级
//    delete _frozenGroup;
//    delete _frozen0;
//    delete _frozen1;
//    delete _frozen2;

//    //boxed
//    delete _boxedGroup;
//    delete _noBox;

//    delete _multiplier;
//    delete _addGroup;

//    delete _blocksBoard;
}
