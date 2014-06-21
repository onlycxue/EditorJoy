#ifndef _BLOCKGROUPDIALOG_H_
#define _BLOCKGROUPDIALOG_H_
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include "groupdata.h"
#include "FileManage/exportfile.h"
class BlockGroupDialog:public QDialog
{
    Q_OBJECT

public:
     BlockGroupDialog(QWidget* parent = 0);
     BlockGroupDialog(const char* file,QWidget* parent=0);
     void init();
     void addGroupItem(QString name,QString num);
     GroupData* findGroupItem(int id);
     int removeGroupIndex(int id);
     int removeGroupItemIndex(GroupData*data,int blockId);
     void showItems(GroupData* group);
     void addItem(int blockId, float weight);
//     QVector<QString> getGroupIds();
     QVector<GroupData*> getGroups();
public slots:

      void addGroup();
      void showGroupItems(QListWidgetItem* item);
      void deleteGroup();
      void deleteGroupItem();
      void exportJsonFile();
signals:
     void groupsSender(QVector<GroupData*>);

private:
     QLabel* _groupNameLabel;
     QLabel* _groupIdLabel;
     QLabel* _blockIdLabel;
     QLabel* _weightLabel;
     QLabel* _groupListName;
     QLabel* _groupItemName;

     QLineEdit* _groupNameEdit;
     QLineEdit* _groupIdEdit;
     QLineEdit* _blockIdEdit;
     QLineEdit* _weightEdit;

     QListWidget* _groupList;
     QListWidget* _itemList;

     QPushButton* _entryButton;
     QPushButton* _deleteGroup;
     QPushButton* _deleteGroupItem;
     QPushButton* _exportButton;

     QHBoxLayout* _mainLayout;

     QVector<GroupData*> _groups;
//     QVector<QString> _groudIds;
};

#endif
