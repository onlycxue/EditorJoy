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
#include "../Block/generalBlock.h"
#include "../Block/commonBlock.h"

class BlockLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BlockLabel(GeneralBlock *item,QWidget *parent = 0);
    BlockLabel(QWidget *parent = 0);
    void setFocusColor(QColor color);
    void setSelect(bool flag);
    bool isSelect();
    GeneralBlock* getPropertys();
    void setProperty(GeneralBlock* item);
    void setSecondImg(const char* fileName);
    void setThirdImg(const char* fileName);
    void propertyInit();
protected:

private:
    GeneralBlock* _propertys;
    QColor _focusColor;
    bool _isSelect;
    QLabel *_secondImgLabel;
    QLabel *_thirdImagLabel;
};

#endif // BLOCKITEM_H
