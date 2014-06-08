#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000,700);
    uiInit();
}

void MainWindow::uiInit()
{

    menubarInit();
    toolbarInit();
    editorWidgetInit();
    blocksWidgetInit();
    ornametalWidgetInit();
    layoutInit();
    statusBarInit();
    connect(_blocksWidget,SIGNAL(Clicked(BlockItem*)),_editorWidget,SLOT(msgHandler(BlockItem*)));
    this->setUpdatesEnabled(true);
    QTimer* timer = new QTimer();
    timer->setInterval(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start();
    connect(_ornamentalWidget,SIGNAL(doubleClicked(QListWidgetItem*)),_editorWidget,SLOT(addDragLabel(QListWidgetItem*)));

    _createDialog = new CreateFile(this);
    _createDialog->show();

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

    _createFile = new QAction("新建...",this);
    filemenu->addAction(_createFile);

    _menus.append(filemenu);

    QMenu* helpmenu = new QMenu(_menubar);
    helpmenu->setObjectName(QStringLiteral("menu"));
    helpmenu->setTitle("帮助");
    _menubar->addMenu(helpmenu);
    _menus.append(helpmenu);

}
void MainWindow::toolbarInit()
{
    _toolbar = new QToolBar(this);
    _toolbar->setObjectName(QStringLiteral("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, _toolbar);

    QAction *newFile = new QAction(QIcon(":/images/Blocks/animal_pig.png"),
                                        "&New",this);
    newFile->setStatusTip("新建文件");
    _toolbar->addAction(newFile);


    QAction *exportFile = new QAction(QIcon(":/images/Blocks/animal_cat.png"),
                                        "&export",this);
    _toolbar->addAction(exportFile);
}
void MainWindow::editorWidgetInit()
{
     _editorArea = new QScrollArea(this);
     _editorArea->setMaximumHeight(540);
     _editorArea->setAlignment(Qt::AlignCenter);
     _editorWidget = new EditorWidget(4,4);
     _editorArea->setWidget(_editorWidget);


    //_editorWidget->setGeometry(300,50,600,600);
    //_editorWidget->setParent(this);
   // _editorArea->resize(600,600);


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
MainWindow::~MainWindow()
{

}
