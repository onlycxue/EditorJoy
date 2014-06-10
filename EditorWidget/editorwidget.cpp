#include "editorwidget.h"

EditorWidget::EditorWidget()
{


}
EditorWidget::EditorWidget(int row,int column):
                      _row(row),_column(column),_selectedNum(-1)
{

    editWidgetInit();
    blocksInit();
    this->setMouseTracking(true);
    actionInit();
    this->setContextMenuPolicy(Qt::DefaultContextMenu);

}
void EditorWidget::editWidgetInit()
{
    _gridLayout = new QGridLayout(this);
    //设置编辑区的背景颜色
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    setPalette(palette);
    resize(BLOCK_WIDTH*(_column+0.2),BLOCK_HEIGHT*(_row+0.2));
}
void EditorWidget::blocksInit()
{

    for(int i = 0 ; i < _row ; i++)
    {
        for(int j = 0; j < _column ; j++)
        {
            qDebug() << "position is " << _row << _column << endl;
            BlockLabel* block = new BlockLabel(this);
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
    return _mouseX;
}
float EditorWidget::getMouseY()
{
    return _mouseY;

}
void EditorWidget::mousePressEvent(QMouseEvent *event)
{
    int num = event->x()/BLOCK_WIDTH + event->y()/BLOCK_HEIGHT*_column;
    qDebug() << event->x()/BLOCK_WIDTH<< "###" << event->y()/BLOCK_HEIGHT <<endl;
    if(_selectedNum != num && num != _column*_row)
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
        qDebug() << "####msgHandle####" << item->_matchType << "##########";
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
    //if()
    qDebug() << "####################" << endl;
    int type = _blocks.at(_selectedNum)->getPropertys()->_type;
    if(type == -1)
        return;

     _mainMenu = new QMenu(this);

//    _colorMenu = _mainMenu->addMenu("color");
//    _colorMenu->addAction(_blueColor);
//    _colorMenu->addAction(_yellowColor);
//    _colorMenu->addAction(_redColor);
//    _colorMenu->addAction(_pinkColor);
//    _colorMenu->addAction(_greenColor);
    setActionStatus();




    _mainMenu->addAction(_addGroup);
    _mainMenu->exec(event->globalPos());


//    QCursor cur=this->cursor();
//    _mainMenu->exec(cur.pos()); //关联到光标
   //获取当前的Label状态

}
//用来处理QAction
void EditorWidget::changeBlockResource(const char* file)
{
    QPixmap pixmap(file);
    if(_selectedNum != -1)
    {
        int width = _blocks.at(_selectedNum)->width();
        int height = _blocks.at(_selectedNum)->height();

        pixmap.scaled(width,height,Qt::KeepAspectRatio);
        _blocks.at(_selectedNum)->setScaledContents(true);

        _blocks.at(_selectedNum)->setPixmap(pixmap);
    }
}
void EditorWidget::setBlueBlock()
{
    if(_selectedNum != -1)
    {
        int type = _blocks.at(_selectedNum)->getPropertys()->_type;
        qDebug() << "########" << type << "##########";
        if(0 <= type&&type<=4)
        {
            changeBlockResource(BlueBlock);
             _blocks.at(_selectedNum)->getPropertys()->_type = 0;
        }
        else if(type == 9)
        {
            changeBlockResource(BlueColorBomb);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 0;
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
             changeBlockResource(YellowBlock);
             _blocks.at(_selectedNum)->getPropertys()->_type = 1;
        }
        else if(type == 9)
        {
            changeBlockResource(YellowColorBomb);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 1;
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
             changeBlockResource(RedBlock);
        }
        else if(type == 9)
        {
            changeBlockResource(RedColorBomb);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 2;
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
             changeBlockResource(GreenBlock);
        }
        else if(type == 9)
        {
            changeBlockResource(GreenColorBomb);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 3;
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
             changeBlockResource(PurpleBlock);
        }
        else if(type == 9)
        {
            changeBlockResource(PurpleColorBomb);
            _blocks.at(_selectedNum)->getPropertys()->_matchType = 4;
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
             _blocks.at(_selectedNum)->getPropertys()->_multiplier = 1;
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
    else if (type == 9)
    {
        int matchType =  _blocks.at(_selectedNum)->getPropertys()->_matchType;
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
void EditorWidget::exportBlocksMsg()
{
    for(int i = 0;i < _blocks.size(); i++)
    {
        qDebug()<<"{" <<endl;
        _blocks.at(i)->getPropertys()->printInfo();
        qDebug()<<"}" <<endl;
    }
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
