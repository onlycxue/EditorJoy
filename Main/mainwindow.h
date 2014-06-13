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
//#include "../DialogWidget/targetdialog.h"
#include "../DialogWidget/backgrounddialog.h"

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

    ~MainWindow();
public slots:
     void update();
     void showCreateDialog();
     void createEditorWidget(DialogMsg* msg);
     void exportFileHandle();
     void importFileHandle();
     void setLevelTargetDialog();
     void editorClose();
     void setLevelTarData(TargetData* data);
     void setLevelBackgroud(QString image);
     //void backgroudDialogshow();
private:

    QToolBar *_toolbar;
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
    BackgroudDialog* _backgroudDialog;
    QLabel *_statusBar;
    QLabel *_posStatusBar;
    QAction *_createFile;
    QAction *_exportFile;
    QAction *_importFile;
    QAction *_editorClose;
    QAction *_levelTarget;
    QAction *_leveBackGround;
    QTimer* _timer;
    CreateFile* _createDialog;

    TargetData* _levelTargetData;
    QString _levelBackground;

};

#endif // MAINWINDOW_H
