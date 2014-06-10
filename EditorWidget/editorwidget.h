#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H
#include <QWidget>
#include <QScrollArea>
#include <QVector>
#include "../Block/blocklabel.h"
#include <QGridLayout>
#include "../Block/blockbutton.h"
#include <QMoveEvent>
#include "../OrnamentalWidget/draglabel.h"
#include <QListWidgetItem>
#include "../Global/globaldef.h"
#include <QActionGroup>

#define BLOCK_WIDTH 70
#define BLOCK_HEIGHT 70



class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    EditorWidget();
    EditorWidget(int row,int column);
    void setRow(int num);
    void setColumn(int num);
    int getRow();
    int getColumn();
    QVector<BlockLabel*> getBlocks();
    void editWidgetInit();
    void blocksInit();
    float getMouseX();
    float getMouseY();
    void actionInit();
    void setActionStatus();
    void setColorActionStatus(int type);
    void setBoxColorActionStatus(int type,bool flag);
    void setForzenStatus(int level);
    void setmultiplyStatus(int level);
    void changeBlockResource(const char* file);
    void exportBlocksMsg();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);
public slots:
    void msgHandler(BlockItem* block);
    void addDragLabel(QListWidgetItem* item);
    void setBlueBlock();
    void setYellowBlock();
    void setRedBlock();
    void setGreenBlock();
    void setPurpleBlock();
    void setFrozen0();
    void setFrozen1();
    void setFrozen2();
    void setmultiply();
    void setNoBox();
private:
    int _row;
    int _column;
    //QWidget* _editWidget;
    QVector<BlockLabel*> _blocks;
    QVector<DragLabel*> _dragLabels;
    int _selectedNum;
    QGridLayout* _gridLayout;
    float _mouseX;
    float _mouseY;

    //右击弹出菜单
    QMenu *_mainMenu;
    QMenu *_colorMenu;
    QMenu *_frozenMenu;
    QMenu *_boxedMenu;

    //二级菜单颜色

    QActionGroup* _colorGroup;
    QAction *_blueColor;
    QAction *_yellowColor;
    QAction *_redColor;
    QAction *_pinkColor;
    QAction *_greenColor;


    //铁笼等级
    QActionGroup* _frozenGroup;
    QAction *_frozen0;
    QAction *_frozen1;
    QAction *_frozen2;

    //boxed
    QActionGroup* _boxedGroup;
    QAction *_noBox;

    QAction *_multiplier;
    QAction *_addGroup;

};

#endif // EDITORWIDGET_H
