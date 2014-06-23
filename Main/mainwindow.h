#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QVector>
#include <QAction>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QTimer>
#include <QGroupBox>
#include "../Global/global.h"
#include "../DialogWidget/createdialogwidget.h"
#include "../Block/blockitem.h"
#include "../FileManage/exportfile.h"
#include "../DialogWidget/backgrounddialog.h"
#include "../DialogWidget/statement.h"
#include "../JsonManage/jsonprotocol.h"
#include <QMessageBox>
#include "../DialogWidget/blockgroupdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void uiInit();
    void menubarInit();
    void toolbarInit();
    void editorWidgetInit();
    void blocksWidgetInit();
    void ornametalWidgetInit();
    void layoutInit();
    void statusBarInit();
    void dialogInit();
    void jsonDataInit();
    ~MainWindow();
public slots:
     void update();
     void createEditorWidget(CreateData* msg);
     void exportFileHandle();
     void importFileHandle();
     void setLevelTargetDialog();
     void editorClose();
     void setLevelTarData(TargetData* data);
     void setLevelBackgroud(QString image);
     //void backgroudDialogshow();
private:

    QToolBar *_fileToolbar;
    QToolBar *_setToolbar;
    QVector<QMenu*> _menus;
    QMenuBar *_menubar;
    QVector<QAction*> _toolbarActions;
    EditorWidget*  _editorWidget;
    QScrollArea* _editorArea;
    QGroupBox*   _blocksBox;
    BlocksWidget* _blocksWidget;
    QHBoxLayout *_hboxLayout;
    QVBoxLayout *_vboxLayout;
    OrnamentalWidget* _ornamentalWidget;

    QLabel *_statusBar;
    QLabel *_posStatusBar;
    QAction *_createFile;
    QAction *_exportFile;
    QAction *_importFile;
    QAction *_editorClose;
    QAction *_levelTarget;
    QAction *_leveBackGround;
    QAction* _groupAction;
    QAction *_statement;
    QTimer* _timer;

    BackgroudDialog* _backgroudDialog;
    CreateFile* _createDialog;
    Statement* _statementDialog;
    TargetDialog* _targetDialog;
    BlockGroupDialog* _groupDialog;
    JsonProtocol* _jsonData;
};

#endif // MAINWINDOW_H
