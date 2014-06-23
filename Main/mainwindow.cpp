#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1100,600);
    uiInit();
}

void MainWindow::uiInit()
{
    jsonDataInit();
    dialogInit();
    menubarInit();
    toolbarInit();
    editorWidgetInit();
    blocksWidgetInit();
    ornametalWidgetInit();
    layoutInit();
    statusBarInit();

    this->setUpdatesEnabled(true);
    _timer = new QTimer();
    _timer->setInterval(50);
    connect(_timer,SIGNAL(timeout()),this,SLOT(update()));

}
void MainWindow::jsonDataInit()
{
    _jsonData = new JsonProtocol;
}
void MainWindow::dialogInit()
{
    _statementDialog = new Statement(this);
    _backgroudDialog = new BackgroudDialog(this);
    connect(_backgroudDialog,SIGNAL(backgroundName(QString)),this,SLOT(setLevelBackgroud(QString)));
    _targetDialog = new TargetDialog(this);
    connect(_targetDialog,SIGNAL(Clicked(TargetData*)),this,SLOT(setLevelTarData(TargetData*)));
    _createDialog = new CreateFile(this);
    connect(_createDialog,SIGNAL(sendMsg(CreateData*)),this,SLOT(createEditorWidget(CreateData*)));
    _groupDialog = new BlockGroupDialog(GroupRulePath,this);

}
void MainWindow::menubarInit()
{
    _menubar = new QMenuBar(this);
    _menubar->setObjectName(QStringLiteral("menuBar"));
    this->setMenuBar(_menubar);

    QMenu* filemenu = new QMenu(_menubar);
    filemenu->setObjectName(QStringLiteral("menu"));
    filemenu->setTitle("文件");
    _menubar->addMenu(filemenu);

    _createFile = new QAction(QIcon(newFileIcon),"新建...",this);
    filemenu->addAction(_createFile);
    connect(_createFile,SIGNAL(triggered()),_createDialog,SLOT(show()));
    _exportFile = new QAction(QIcon(exportfileIcon),"导出...",this);
    filemenu->addAction(_exportFile);  
    connect(_exportFile,SIGNAL(triggered()),this,SLOT(exportFileHandle()));
    _importFile = new QAction(QIcon(importFileIcon),"导入...",this);
    filemenu->addAction(_importFile);
    connect(_importFile,SIGNAL(triggered()),this,SLOT(importFileHandle()));

    _editorClose = new QAction(QIcon(exitFileIcon),"关闭",this);
    filemenu->addAction(_editorClose);
    connect(_editorClose,SIGNAL(triggered()),this,SLOT(editorClose()));  
    _menus.append(filemenu);

    QMenu* setmenu = new QMenu(_menubar);
    setmenu->setObjectName(QStringLiteral("menu"));
    setmenu->setTitle("设置");
    _menubar->addMenu(setmenu);
    _menus.append(setmenu);
    _levelTarget = new QAction(QIcon(levelTargetIcon),"关卡目标",this);
    setmenu->addAction(_levelTarget);

    connect(_levelTarget,SIGNAL(triggered()),_targetDialog,SLOT(show()));
    _leveBackGround = new QAction(QIcon(levelBackgroundIcon),"关卡背景",this);
    connect(_leveBackGround,SIGNAL(triggered()),_backgroudDialog,SLOT(show()));
    setmenu->addAction(_leveBackGround);
    QAction* groupAction = new QAction("添加组",this);
    setmenu->addAction(groupAction);
    connect(groupAction,SIGNAL(triggered()),_groupDialog,SLOT(show()));

    QMenu* helpmenu = new QMenu(_menubar);
    helpmenu->setObjectName(QStringLiteral("menu"));
    helpmenu->setTitle("帮助");
    _statement = new QAction("关于",this);
    helpmenu->addAction(_statement);
    connect(_statement,SIGNAL(triggered()),_statementDialog,SLOT(show()));
    _menubar->addMenu(helpmenu);
    _menus.append(helpmenu);



}
void MainWindow::toolbarInit()
{
    _toolbar = new QToolBar(this);
    _toolbar->setObjectName(QStringLiteral("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, _toolbar);

    QAction *newFile = new QAction(QIcon(newFileIcon),
                                        "&New",this);
    connect(newFile,SIGNAL(triggered()),_createDialog,SLOT(show()));
    newFile->setStatusTip("新建文件");
    _toolbar->addAction(newFile);

    QAction *exportFile = new QAction(QIcon(exportfileIcon),
                                        "&export",this);
    _toolbar->addAction(exportFile);
    connect(exportFile,SIGNAL(triggered()),this,SLOT(exportFileHandle()));

    QAction *importFile = new QAction(QIcon(importFileIcon),
                                        "&import",this);
    _toolbar->addAction(importFile);
    connect(importFile,SIGNAL(triggered()),this,SLOT(importFileHandle()));

    QAction *exitFile= new QAction(QIcon(exitFileIcon),
                                        "&exit",this);
    _toolbar->addAction(exitFile);
    connect(exitFile,SIGNAL(triggered()),this,SLOT(editorClose()));
}
void MainWindow::editorWidgetInit()
{
     _editorArea = new QScrollArea(this);
     _editorArea->setMaximumHeight(540);
     _editorArea->setAlignment(Qt::AlignCenter);
     _editorWidget = NULL;
}
void MainWindow::blocksWidgetInit()
{
    //_blocksBox = new QGroupBox(this);
    _blocksWidget = new BlocksWidget(this);
    //_blocksBox->setTitle("道具");

}
void MainWindow::ornametalWidgetInit()
{
    _ornamentalWidget = new OrnamentalWidget(this);

}
void MainWindow::layoutInit()
{

    _vboxLayout = new QVBoxLayout;

    _hboxLayout = new QHBoxLayout;
    _hboxLayout->addWidget(_blocksWidget);
    _hboxLayout->addWidget(_editorArea);
    _hboxLayout->addWidget(_ornamentalWidget);

    _vboxLayout->addStretch(200);
    _vboxLayout->addLayout(_hboxLayout);

    QWidget* widget = new QWidget(this);
    widget->setLayout(_vboxLayout);
    this->setCentralWidget(widget);
}
void MainWindow::statusBarInit()
{
    _statusBar = new QLabel;
    _statusBar->setMinimumSize(_statusBar->sizeHint());
    _statusBar->setAlignment(Qt::AlignHCenter);

    _posStatusBar = new QLabel;
    _statusBar->setMinimumSize(_posStatusBar->sizeHint());
    _statusBar->setAlignment(Qt::AlignCenter);

    statusBar()->addWidget(_statusBar,100);
    statusBar()->addWidget(_posStatusBar,480);

}
void MainWindow::update()
{

    QString mouseX;
    mouseX.setNum(_editorWidget->getMouseX());
    QString mouseY;
    mouseY.setNum(_editorWidget->getMouseY());

    QString str = QString("X: ")+mouseX+QString("  ") +QString("Y: ")+mouseY;
   // statusBar()->setToolTip(str);
    _posStatusBar->setText(str);


}

void MainWindow::createEditorWidget(CreateData* msg)
{

    if(0 < msg->getColumn()&&msg->getColumn() <= 9 && 5 < msg->getRow()&&msg->getRow() <= 12)
    {
        _editorWidget = new EditorWidget(msg->getRow(),msg->getColumn());
        _editorArea->setWidget(_editorWidget);
        connect(_blocksWidget,SIGNAL(Clicked(GeneralBlock*)),_editorWidget,SLOT(msgHandler(GeneralBlock*)));
        connect(_ornamentalWidget,SIGNAL(doubleClicked(QListWidgetItem*)),_editorWidget,SLOT(addDragLabel(QListWidgetItem*)));
        connect(_groupDialog,SIGNAL(groupsSender(QVector<GroupData*>)),_editorWidget,SLOT(getGroupsFromDialog(QVector<GroupData*>)));
        _editorWidget->setBlockGroupRule(_groupDialog->getGroups());
        char imageDir[200];
        sprintf(imageDir,"%s/%s",BackGroundBasePath,msg->getBackground().toUtf8().data());
        _editorWidget->setBlocksBoardImg(imageDir);
        qDebug() << msg->getBackground();
       // delete msg;
        _timer->start();
        _createDialog->close();
        //save data
        _jsonData->setCreateData(msg);
    }
    else
    {

        int ret = QMessageBox::warning(this, tr("warn"),
                                       tr(" 5 < row 13 and  0 < colum <= 9"),
                                          QMessageBox::Ok);
    }
}
void MainWindow::exportFileHandle()
{
    if(_editorWidget != NULL)
    {
//        if(_levelTargetData == NULL || _levelBackground == QString::null)
//        {
//            int ret = QMessageBox::warning(this, tr("warn"),
//                                           tr("请先确保关卡目标或关卡背景已经设置！"),
//                                              QMessageBox::Ok);
//        }
//        else
        {
           _editorWidget->exportBlocksMsg();
//          QJsonDocument document = JsonHandle::getInstance()->exportJson(_editorWidget->getBlocks(),_editorWidget->getConstraints(),
//                                                  _editorWidget->getRow(),_editorWidget->getColumn(),_levelTargetData,_levelBackground);
           _jsonData->setBlocks(_editorWidget->getBlocks());
           _jsonData->setTarget(_targetDialog->getTatgetData());
           _jsonData->setConstraints(_editorWidget->getConstraints());
           _jsonData->setGroupRules(_groupDialog->getGroups());
           qDebug() << "####document front#####" <<endl;
           QJsonDocument document = JsonHandle::getInstance()->exportJson(_jsonData);
           qDebug() << "####document last#####" <<endl;
           new ExportFile(document,this);
        }
    }
    else
    {
        int ret = QMessageBox::warning(this, tr("warn"),
                                       tr("请先创建关卡文件"),
                                          QMessageBox::Ok);
    }
}
void MainWindow::importFileHandle()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "./Export",
                                                    tr("Text files (*.json)"));
    _jsonData=JsonHandle::getInstance()->importJson(fileName.toUtf8().data());
    qDebug() << "import start!"<<endl;
    _editorWidget = new EditorWidget(_jsonData);
    _editorArea->setWidget(_editorWidget);
    connect(_blocksWidget,SIGNAL(Clicked(GeneralBlock*)),_editorWidget,SLOT(msgHandler(GeneralBlock*)));
    connect(_ornamentalWidget,SIGNAL(doubleClicked(QListWidgetItem*)),_editorWidget,SLOT(addDragLabel(QListWidgetItem*)));
    connect(_groupDialog,SIGNAL(groupsSender(QVector<GroupData*>)),_editorWidget,SLOT(getGroupsFromDialog(QVector<GroupData*>)));
    qDebug() << "import endl!"<<endl;
    _timer->start();


}
void MainWindow::editorClose()
{
    _timer->stop();
    delete _editorWidget;

    _editorWidget = NULL;
}
void MainWindow::setLevelTargetDialog()
{

}
void MainWindow::setLevelTarData(TargetData* data)
{
    if(_editorWidget != NULL)
    {
        //save data;
        _jsonData->setTarget(data);
    }
    else
    {
        int ret = QMessageBox::warning(this, tr("warn"),
                                       tr("请先创建关卡文件"),
                                          QMessageBox::Ok);
        _targetDialog->hide();
    }
}

void MainWindow::setLevelBackgroud(QString image)
{
    if(_editorWidget != NULL)
    {
        char fileName[200];
        sprintf(fileName,"%s/%s",BackGroundBasePath,image.toUtf8().data());
        qDebug() <<"Board image is " <<fileName;
        _editorWidget->setBlocksBoardImg(fileName);
        //save background
       // _jsonData->getCreateData()->setBackground(image.split(".").front());

    }
    else
    {
        int ret = QMessageBox::warning(this, tr("warn"),
                                       tr("请先创建关卡文件"),
                                          QMessageBox::Ok);
        _backgroudDialog->hide();
    }

}

MainWindow::~MainWindow()
{

}
