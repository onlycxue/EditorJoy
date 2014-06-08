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
#include "editorwidget.h"
#include "blockswidget.h"
#include <QHBoxLayout>
#include "ornamentalwidget.h"
#include <QStatusBar>
#include <QTimer>
#include <QGroupBox>


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
    QLabel *_statusBar;
    QLabel *_posStatusBar;

};

#endif // MAINWINDOW_H
