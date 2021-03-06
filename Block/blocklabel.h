#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include <QLabel>
#include <QWidget>
#include "blockitem.h"
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QColor>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include "../Global/globaldef.h"

class BlockLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BlockLabel(BlockItem *item,QWidget *parent = 0);
    BlockLabel(QWidget *parent = 0);
    void setFocusColor(QColor color);
    void setSelect(bool flag);
    bool isSelect();
    BlockItem* getPropertys();
    void setProperty(BlockItem* item);
    void setSecondImg(const char* fileName);
    void setThirdImg(const char* fileName);
    void propertyInit();
protected:

private:
    BlockItem* _propertys;
    QColor _focusColor;
    bool _isSelect;
    QLabel *_secondImgLabel;
    QLabel *_thirdImagLabel;
};

#endif // BLOCKITEM_H
