#ifndef BLOCKSWIDGET_H
#define BLOCKSWIDGET_H
#include <QWidget>
#include <QVector>
#include "blocklabel.h"
#include "../JsonManage/jsonhandle.h"
#include <QDebug>
#include <QPalette>
#include <QGridLayout>
#include "blockbutton.h"
#include <QLabel>
#include <QGroupBox>
//用来显示所有block控件
class BlocksWidget:public QWidget
{
    Q_OBJECT
public:
    BlocksWidget(QWidget* parent = 0);
//    bool readBlockConfig(const char* configFile);
    void blocksInit();
private:
    BlockItemArray _items;
    QVector<BlockLabel*> _blocks;
    const char* _configFile;
    QGridLayout* _gridLayout;
    QLabel* _nameLabel;
   // QGroupBox* _box;
signals:
    void Clicked(BlockItem* );
};

#endif // BLOCKSWIDGET_H
