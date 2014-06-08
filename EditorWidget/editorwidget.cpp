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
     qDebug() << event->x()<< "@@@" << event->y()<<endl;
     _mouseX = event->x();
     _mouseY = event->y();

}
void EditorWidget::msgHandler(BlockItem* item)
{
    QPixmap pixmap(item->_resource);
    if(_selectedNum != -1)
    {
        int width = _blocks.at(_selectedNum)->width();
        int height = _blocks.at(_selectedNum)->height();

        pixmap.scaled(width,height,Qt::KeepAspectRatio);
        _blocks.at(_selectedNum)->setScaledContents(true);

        _blocks.at(_selectedNum)->setPixmap(pixmap);
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
    _blueColor = new QAction(tr("blue"),this);
    _yellowColor = new QAction(tr("yellow"),this);
    _redColor = new QAction(tr("red"),this);
    _pinkColor = new QAction(tr("pink"),this);
    _greenColor = new QAction(tr("green"),this);
    //铁笼等级
    _frozen1 = new QAction(tr("level1"),this);
    _frozen2 = new QAction(tr("level2"),this);

    _multiplier = new QAction(tr("multiplier"),this);
    _addGroup = new QAction(tr("addGroup"),this);



}
void EditorWidget::contextMenuEvent(QContextMenuEvent *event)
{
    //if()
    qDebug() << "####################" << endl;
     _mainMenu = new QMenu(this);
    _colorMenu = _mainMenu->addMenu("color");
    _colorMenu->addAction(_blueColor);
    _colorMenu->addAction(_yellowColor);
    _colorMenu->addAction(_redColor);
    _colorMenu->addAction(_pinkColor);
    _colorMenu->addAction(_greenColor);

    _frozenMenu = _mainMenu->addMenu("frozen");
    _frozenMenu->addAction(_frozen1);
    _frozenMenu->addAction(_frozen2);

    _mainMenu->addAction(_multiplier);
    _mainMenu->addAction(_addGroup);
    _mainMenu->exec(event->globalPos());

//    QCursor cur=this->cursor();
//    _mainMenu->exec(cur.pos()); //关联到光标
}
