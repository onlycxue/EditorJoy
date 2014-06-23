#include "editorwidget.h"

EditorWidget::EditorWidget(JsonProtocol* data):_touchingLabel(NULL),_selectedNum(-1)
{
    _row = data->getCreateData()->getRow();
    _column = data->getCreateData()->getColumn();
    _dragLabels = data->getConstraints();


    editWidgetInit();
    blocksInit();
    this->setMouseTracking(true);
    actionInit();

    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    for(int i = 0 ; i < _row*_column;i++)
    {
        _blocks.at(i)->setProperty(data->getBlocks().at(i));
        setBlocksStatus(_blocks.at(i));
    }
    qDebug() << _dragLabels.size()<< "&*&*&*&*&*";
    for(int i = 0 ; i < _dragLabels.size(); i++)
    {
        _dragLabels.at(i)->setParent(this);
        connect(_dragLabels.at(i),SIGNAL(sendTouchingLabel(DragLabel*)),this,SLOT(touchingLabel(DragLabel*)));
        connect(_dragLabels.at(i),SIGNAL(sendTouchEnd()),this,SLOT(touchingClean()));
        connect(_dragLabels.at(i),SIGNAL(sendDeleteLabel(DragLabel*)),this,SLOT(deleteDragLabel(DragLabel*)));

    }

    char imageDir[200];
    sprintf(imageDir,"%s/%s.png",BackGroundBasePath,data->getCreateData()->getBackground().toUtf8().data());
    qDebug() <<"hi charly image dir is "<<imageDir;
    setBlocksBoardImg(imageDir);
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
    this->setMinimumSize(640,1200);
    _blocksBoard = new QWidget(this);
    _blocksBoard->show();
    _blocksBoard->setGeometry(0,0,BLOCK_WIDTH*(_column+0.2),BLOCK_HEIGHT*(_row+0.2));
    _blocksBoard->setAttribute(Qt::WA_TransparentForMouseEvents);
    _blocksBoard->setWindowFlags(Qt::WindowStaysOnTopHint);
    _blocksBoard->raise();
   // _gridLayout = new QGridLayout(_blocksBoard);
    //设置编辑区的背景颜色
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,253,123));
    setPalette(palette);
    _blocksBoard->setMinimumSize(BLOCK_WIDTH*(_column+0.2),BLOCK_HEIGHT*(_row+0.2));
   // this->resize(640,1640);    //9行、
    //this->resize(640,1480);      // 8 hang
    //this->resize(640,1270);  //7 hang
//    this->resize(640,1100);    //6hang
//    if(_row == 9)
//    {
//        this->resize(640,1640);
//    }
//    else if(_row == 8)
//    {
//        this->resize(640,1480);
//    }
//    else if(_row == 7)
//    {
//        this->resize(640,1270);
//    }
//    else if(_row == 6)
//    {
//        this->resize(640,1100);
//    }
//    else
//    {
//        this->resize(640,1280);
//    }

    int x =(width()-BLOCK_WIDTH*(_column+0.2))/2;
    int y =(height() - BLOCK_HEIGHT*(_row+0.2))/2;

//    int blockOffset =0;
//    if (_column==5) {
//        blockOffset=-70;
//    }else if (_column==6){
//        blockOffset=30;
//    }else if (_column==7){
//        blockOffset=160 ;
//    }else if (_column==8){
//        blockOffset=120;
//    }else if (_column==9){
//        blockOffset=360;
//    }
    //qDebug() << "############X:"<< x << "y:" << y <<"###############" <<this->size()<<endl;
    //_blocksBoard->setGeometry(x,y+blockOffset,_blocksBoard->width(),_blocksBoard->height());
    //qDebug() << "############X:"<< x << "y:" << y <<"###############" <<_blocksBoard->size()<<endl;
}
void EditorWidget::blocksInit()
{
    float blockOffset = 0;

    if (_column==5) {
        blockOffset=143;
    }else if (_column==6){
        blockOffset=108;
    }else if (_column==7){
        blockOffset=73 ;
    }else if (_column==8){
        blockOffset=38 ;
    }else {
        blockOffset=3;
    }

    int yOffset = 146;
    int scrollHeight = 1200;
    int blocksHeight = 63*(_row-1)+70;
    int offsetHeight = scrollHeight - blocksHeight;

    for(int i = 0 ; i < _row ; i++)
    {
        for(int j = 0; j < _column ; j++)
        {
            //qDebug() << "position is " << _row << _column << endl;
            BlockLabel* block = new BlockLabel(this);
            //block->installEventFilter(this);
            block->setAttribute(Qt::WA_TransparentForMouseEvents);
            block->setGeometry(QRect(blockOffset + 70*j ,  offsetHeight+63*i - yOffset,BLOCK_WIDTH,BLOCK_HEIGHT));
            qDebug() <<"@#block Location is " << block->geometry();
            _blocks.append(block);
            //_gridLayout->addWidget(block,i,j);
        }
    }
    _blocksArea = new QRect(blockOffset,offsetHeight-yOffset,_column*BLOCK_WIDTH,blocksHeight);

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
BlockLabel* EditorWidget::getSelectBlock()
{
    if(_selectedNum == -1)
    {
        return NULL;
    }
    return _blocks.at(_selectedNum);
}
void EditorWidget::mousePressEvent(QMouseEvent *event)
{

     if(_blocksArea->contains(event->x(),event->y()))
     {
         int num = (event->x()- _blocksArea->x())/BLOCK_WIDTH + (event->y()-_blocksArea->y())/63*_column;
         if(_selectedNum != num && num < _column*_row)
         {

             if(_selectedNum != -1)
             {
                getSelectBlock()->setSelect(false);
             }
             _selectedNum = num;
             getSelectBlock()->setSelect(true);
         }
     }

}

void EditorWidget::mouseMoveEvent(QMouseEvent *event)
{
//     qDebug() << event->x()<< "@@@" << event->y()<<endl;
     _mouseX = event->x();
     _mouseY = event->y();

}

void EditorWidget::msgHandler(GeneralBlock* item)
{
    //要判断一下type是否为-1
    QPixmap pixmap(item->getResource());
    if(_selectedNum != -1)
    {
        int width = getSelectBlock()->width();
        int height = getSelectBlock()->height();

        pixmap.scaled(width,height,Qt::KeepAspectRatio);
        getSelectBlock()->setScaledContents(true);

        getSelectBlock()->setPixmap(pixmap);
        getSelectBlock()->setProperty(item);
        getSelectBlock()->getPropertys()->printInfo();
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

    label->setImage(item->text().split(".").front());
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
    _groupsActionGroup = new QActionGroup(this);
    connect(_groupsActionGroup,SIGNAL(triggered(QAction*)),this,SLOT(groupActionSelect(QAction*)));
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
    int type = getSelectBlock()->getPropertys()->getType();
    if(type == -1)
        return;

     _mainMenu = new QMenu(this);
    setActionStatus();
//    _mainMenu->addAction(_addGroup);
    _mainMenu->exec(event->globalPos());

}

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

    if(getSelectBlock())
    {
        QString name = getSelectBlock()->getPropertys()->getPillarName();
        if(name.compare("PRRuleCommonBlock") == 0)
        {
            changeBlockResource(BlueBlock,getSelectBlock());
            getSelectBlock()->getPropertys()->setType(BLUE);
        }
        else if(name.compare("PRRuleColorBombBlock") == 0)
        {
            ColorBombBlock* block= (ColorBombBlock*)getSelectBlock()->getPropertys();
            changeBlockResource(BlueColorBomb,getSelectBlock());
            block->setType(7);
            block->setColorBombMatchType(BLUE);
        }
        else if(name.compare("PRRulePetBlock") == 0)
        {
            PetBlock* block= (PetBlock*)getSelectBlock()->getPropertys();
           // changeBlockResource(BlueCarrier);
            block->setMatchType(BLUE);
            block->setBoxedable(true);
            getSelectBlock()->setSecondImg(BlueCarrier);
        }
    }

}
void EditorWidget::setYellowBlock()
{
    qDebug() << "in setYellowBlock function" << endl;
    if(getSelectBlock())
    {
        qDebug() << "getSelectblock is Ok";
        QString name = getSelectBlock()->getPropertys()->getPillarName();

        if(name.compare("PRRuleCommonBlock") == 0)
        {
            changeBlockResource(YellowBlock,getSelectBlock());
            getSelectBlock()->getPropertys()->setType(YELLOW);
            getSelectBlock()->getPropertys()->setMatchType(YELLOW);
        }
        else if(name.compare("PRRuleColorBombBlock") == 0)
        {
            ColorBombBlock* block= (ColorBombBlock*)getSelectBlock()->getPropertys();
            changeBlockResource(YellowColorBomb,getSelectBlock());
            block->setType(8);
            block->setColorBombMatchType(YELLOW);
        }
        else if(name.compare("PRRulePetBlock") == 0)
        {
            PetBlock* block= (PetBlock*)getSelectBlock()->getPropertys();
           // changeBlockResource(BlueCarrier);
            block->setMatchType(YELLOW);
            block->setBoxedable(true);
            getSelectBlock()->setSecondImg(YellowCarrier);
        }

    }
}
void EditorWidget::setRedBlock()
{
    if(getSelectBlock())
    {
        QString name = getSelectBlock()->getPropertys()->getPillarName();

        if(name.compare("PRRuleCommonBlock") == 0)
        {
            changeBlockResource(RedBlock,getSelectBlock());
            getSelectBlock()->getPropertys()->setType(RED);
            getSelectBlock()->getPropertys()->setMatchType(RED);
        }
        else if(name.compare("PRRuleColorBombBlock") == 0)
        {
            ColorBombBlock* block= (ColorBombBlock*)getSelectBlock()->getPropertys();
            changeBlockResource(RedColorBomb,getSelectBlock());
            block->setType(9);
            block->setColorBombMatchType(RED);
        }
        else if(name.compare("PRRulePetBlock") == 0)
        {
            PetBlock* block= (PetBlock*)getSelectBlock()->getPropertys();
           // changeBlockResource(BlueCarrier);
            block->setMatchType(RED);
            block->setBoxedable(true);
            getSelectBlock()->setSecondImg(RedCarrier);
        }
   }
}
void EditorWidget::setGreenBlock()
{
    if(getSelectBlock())
    {
        QString name = getSelectBlock()->getPropertys()->getPillarName();

        if(name.compare("PRRuleCommonBlock") == 0)
        {
            changeBlockResource(GreenBlock,getSelectBlock());
            getSelectBlock()->getPropertys()->setType(GREEN);
            getSelectBlock()->getPropertys()->setMatchType(GREEN);
        }
        else if(name.compare("PRRuleColorBombBlock") == 0)
        {
            ColorBombBlock* block= (ColorBombBlock*)getSelectBlock()->getPropertys();
            changeBlockResource(GreenColorBomb,getSelectBlock());
            block->setType(10);
            block->setColorBombMatchType(GREEN);
        }
        else if(name.compare("PRRulePetBlock") == 0)
        {
            PetBlock* block= (PetBlock*)getSelectBlock()->getPropertys();
           // changeBlockResource(BlueCarrier);
            block->setMatchType(GREEN);
            block->setBoxedable(true);
            getSelectBlock()->setSecondImg(GreenCarrier);
        }
   }
}
void EditorWidget::setPurpleBlock()
{
    if(getSelectBlock())
    {
        QString name = getSelectBlock()->getPropertys()->getPillarName();

        if(name.compare("PRRuleCommonBlock") == 0)
        {
            changeBlockResource(PurpleBlock,getSelectBlock());
            getSelectBlock()->getPropertys()->setType(PURPLE);
            getSelectBlock()->getPropertys()->setMatchType(PURPLE);
        }
        else if(name.compare("PRRuleColorBombBlock") == 0)
        {
            ColorBombBlock* block= (ColorBombBlock*)getSelectBlock()->getPropertys();
            changeBlockResource(PurpleColorBomb,getSelectBlock());
            block->setType(11);
            block->setColorBombMatchType(PURPLE);
        }
        else if(name.compare("PRRulePetBlock") == 0)
        {
            PetBlock* block= (PetBlock*)getSelectBlock()->getPropertys();
           // changeBlockResource(BlueCarrier);
            block->setMatchType(PURPLE);
            block->setBoxedable(true);
            getSelectBlock()->setSecondImg(PurpleCarrier);
        }
   }

}
void EditorWidget::setFrozen0()
{
    QString name = getSelectBlock()->getPropertys()->getPillarName();
    if(name.compare("PRRuleCommonBlock")==0)
    {
         CommonBlock *commonBlock= (CommonBlock*)getSelectBlock()->getPropertys();
         commonBlock->setFrozenLevel(0);
         commonBlock->setFrozenable(false);
         getSelectBlock()->setSecondImg("");
         getSelectBlock()->setThirdImg("");
    }
}
void EditorWidget::setFrozen1()
{
    QString name = getSelectBlock()->getPropertys()->getPillarName();
    if(name.compare("PRRuleCommonBlock")==0)
    {
         CommonBlock *commonBlock= (CommonBlock*)getSelectBlock()->getPropertys();
         commonBlock->setFrozenLevel(1);
         commonBlock->setFrozenable(true);
         getSelectBlock()->setSecondImg(FrozenLevel1);
         getSelectBlock()->setThirdImg("");
    }
}
void EditorWidget::setFrozen2()
{
    QString name = getSelectBlock()->getPropertys()->getPillarName();
    if(name.compare("PRRuleCommonBlock")==0)
    {
         CommonBlock *commonBlock= (CommonBlock*)getSelectBlock()->getPropertys();
         commonBlock->setFrozenLevel(2);
         commonBlock->setFrozenable(true);
         getSelectBlock()->setSecondImg(FrozenLevel1);
         getSelectBlock()->setThirdImg(FrozenLevel2);
    }
}
void EditorWidget::setmultiply()
{
    QString name = getSelectBlock()->getPropertys()->getPillarName();
    if(name.compare("PRRuleCommonBlock") == 0)
    {
        CommonBlock *commonBlock= (CommonBlock*)getSelectBlock()->getPropertys();
        if(commonBlock->getMultipliper() == 0)
        {
            commonBlock->setMultipliper(2);
            getSelectBlock()->setSecondImg(MultiplyFlag);
        }
        else
        {
            commonBlock->setMultipliper(0);
            getSelectBlock()->setSecondImg("");
        }
    }
}

void EditorWidget::setNoBox()
{
    QString name = getSelectBlock()->getPropertys()->getPillarName();
    if(name.compare("PRRulePetBlock") == 0)
    {
        PetBlock* petBlock = (PetBlock*)(getSelectBlock()->getPropertys());
        petBlock->setBoxedable(false);
        getSelectBlock()->setSecondImg("");
    }
}

void EditorWidget::setColorActionStatus(int type)
{
    _colorMenu = _mainMenu->addMenu("color");
    _colorMenu->addAction(_blueColor);
    _colorMenu->addAction(_yellowColor);
    _colorMenu->addAction(_redColor);
    _colorMenu->addAction(_pinkColor);
    _colorMenu->addAction(_greenColor);
//    _colorMenu->addActions(_colorGroup->actions());
//    qDebug() <<"action Size:"<< _colorGroup->actions().size();

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
                //getSelectBlock()->setSecondImg("");
                //getSelectBlock()->setThirdImg("");
                _frozen0->setChecked(true);
                _frozen1->setChecked(false);
                _frozen2->setChecked(false);
                break;
        case 1:
               //getSelectBlock()->setSecondImg(FrozenLevel1);
               _frozen0->setChecked(false);
               _frozen1->setChecked(true);
               _frozen2->setChecked(false);
               break;
        case 2:
               //getSelectBlock()->setThirdImg(FrozenLevel2);
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
//            getSelectBlock()->setSecondImg("");
//            getSelectBlock()->setThirdImg("");
            _multiplier->setChecked(false);
            break;
        case 1:
//            getSelectBlock()->setSecondImg(MultiplyFlag);
            _multiplier->setChecked(true);
            break;
        default:
            break;

    }
}
void EditorWidget::setActionStatus()
{

    QString name = getSelectBlock()->getPropertys()->getPillarName();
    qDebug() << "#######" << name << "####"<< endl;
    if(name.compare("PRRuleCommonBlock") == 0)
    {
        CommonBlock* commonBlock = (CommonBlock*)getSelectBlock()->getPropertys();
        int type = commonBlock->getType();
        int frozenLevel = commonBlock->getFrozenLevel();
        int multiPly = commonBlock->getMultipliper();
        setColorActionStatus(type);
        setForzenStatus(frozenLevel);
        setmultiplyStatus(multiPly);
    }
    else if (name.compare("PRRuleColorBombBlock") == 0)
    {
        ColorBombBlock* colorBomb = (ColorBombBlock*)getSelectBlock()->getPropertys();
        int matchType = colorBomb->getColorBombMatchType();
        setColorActionStatus(matchType);
    }
    else if(name.compare("PRRulePetBlock") == 0)
    {
        PetBlock* petBlock = (PetBlock*)getSelectBlock()->getPropertys();
        int matchType =  petBlock->getMatchType();
        bool boxedFlag = petBlock->getBoxedable();
        qDebug() << "boxed flag is " << boxedFlag;
        setBoxColorActionStatus(matchType,boxedFlag);
    }
    else if(name.compare("PRRuleRanddomBlock") == 0)
    {
        setRandomBlockStatus();
        qDebug() << "randdomBlock" << endl;
    }

}
QString EditorWidget::getResourceFromConfig(QString name)
{
       qDebug() << "current name is " << name;
      QVector<GeneralBlock*> array = JsonHandle::getInstance()->parserConfigJson(BlockConfigPath,JsonHandle::ConfigFile);
      for(int i = 0 ; i < array.size(); i++)
      {
            qDebug() << "{" ;
            array.at(i)->printInfo();
            qDebug() << "}";
            if(name.compare(array.at(i)->getPillarName()) == 0)
            {
                return array.at(i)->getResource();
            }
      }
      return QString::null;
}
void EditorWidget::setBlocksStatus(BlockLabel* item)
{
    QString name = item->getPropertys()->getPillarName();
    if(name.compare("PRRuleCommonBlock")==0)
    {
        CommonBlock* commonBlock = (CommonBlock*) item;

        int frozenLevel = commonBlock->getFrozenLevel();
        int multiplyFlag = commonBlock->getMultipliper();
        bool frozen = commonBlock->getFrozenable();
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
    else if(name.compare("PRRuleColorBombBlock") == 0)
    {
        setBlockColor(item);
    }
    else if(name.compare("PRRulePetBlock") == 0)
    {
        PetBlock* petBlock = (PetBlock*)item;
        if(petBlock->getBoxedable())
        {
            setPetBoxedColor(item);
        }
        else
        {
            QString imageName = EditorWidget::getResourceFromConfig(item->getPropertys()->getPillarName());
            changeBlockResource(imageName.toUtf8().data(),item);
        }
    }
    else
    {

        QString imageName = EditorWidget::getResourceFromConfig(item->getPropertys()->getPillarName());
        changeBlockResource(imageName.toUtf8().data(),item);

    }
}
void EditorWidget::setBlockColor(BlockLabel*  item)
{
    switch(item->getPropertys()->getType())
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
    switch(item->getPropertys()->getMatchType())
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
QVector<GeneralBlock*> EditorWidget::getBlocks()
{
    _generalBlocks.clear();
    for(int i = 0 ; i < _blocks.size();i++)
    {
        _generalBlocks.append(_blocks.at(i)->getPropertys());
    }
    return _generalBlocks;
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
//void EditorWidget::setLevelTatget(TargetData* data)
//{
//    _levelTarget->petNum = data->petNum;
//    _levelTarget->star1Score = data->star1Score;
//    _levelTarget->star2Score = data->star2Score;
//    _levelTarget->star3Score = data->star3Score;
//}

void EditorWidget::setBlocksBoardImg(QString image)
{

    //this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap img(image);
    //img.scaled(640,1200);
    img.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    palette.setBrush(QPalette::Background, QBrush(img));
    this->setPalette(palette);

}
void EditorWidget::getGroupsFromDialog(QVector<GroupData*> groups)
{

    QAction* action = new QAction(groups.last()->getName(),this);
    _groupsActionGroup->addAction(action);
    //connect(action,SIGNAL(triggered()),this,SLOT(groupActions()));
}
void EditorWidget::setBlockGroupRule(QVector<GroupData*> data)
{
    _blockGroups = data;
    for(int i = 0; i < data.size();i++)
    {
        QString id;
        id.setNum(data.at(i)->getGroupId());
        QAction* action = new QAction(id,this);
        //action->setCheckable(true);
       // connect(action,SIGNAL(triggered()),this,SLOT(groupActions()));
        _groupsActionGroup->addAction(action);
    }
    //getGroupsFromDialog(data);
}
void EditorWidget::groupActionSelect(QAction* action)
{
//    for(int i = 0 ; i < _blockGroups.size(); i++)
//    {
//        if(_blockGroups.at(i)->getName() == action->text())
//        {
//            int id = _blockGroups.at(i)->getGroupId();
//            getSelectBlock()->getPropertys()->setBlockId(id);
//            break;
//        }
//    }
     getSelectBlock()->getPropertys()->setBlockId(action->text().toInt());
}

void EditorWidget::setRandomBlockStatus()
{
    _groupsMenu =  _mainMenu->addMenu("addGroup");
    _groupsMenu->addActions(_groupsActionGroup->actions());

}
EditorWidget::~EditorWidget()
{

}
