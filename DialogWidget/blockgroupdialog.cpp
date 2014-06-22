#include "blockgroupdialog.h"
BlockGroupDialog::BlockGroupDialog(QWidget* parent):
    QDialog(parent)
{
    init();
    resize(400,300);
}
BlockGroupDialog::BlockGroupDialog(const char* file,QWidget* parent):
    QDialog(parent)
{
    init();
    resize(400,300);

    QJsonArray array = JsonHandle::getInstance()->parserJsonFileForGrouprule(file);
    for(int i = 0; i< array.size();i++)
    {
        GroupData* data = new GroupData(array.at(i).toObject());
        _groups.append(data);
        qDebug() <<"#*"<<_groups.at(i)->getGroupItems().size();

    }
    for(int i = 0; i < _groups.size();i++)
    {
        QString id;
        id.setNum(_groups.at(i)->getGroupId());
        addGroupItem(_groups.at(i)->getName(),id);
    }

}
void BlockGroupDialog::init()
{
    QHBoxLayout *groupNameLayout = new QHBoxLayout;
    _groupNameLabel = new QLabel(this);
    _groupNameLabel->setText("组名:");
    _groupNameEdit = new QLineEdit(this);
    groupNameLayout->addWidget(_groupNameLabel);
    groupNameLayout->addWidget(_groupNameEdit);

    QHBoxLayout *groupIdLayout = new QHBoxLayout;
    _groupIdLabel = new QLabel(this);
    _groupIdLabel->setText("组Id:");
    _groupIdEdit = new QLineEdit(this);
    groupIdLayout->addWidget(_groupIdLabel);
    groupIdLayout->addWidget(_groupIdEdit);



    QHBoxLayout *blockIdLayout = new QHBoxLayout;
    _blockIdLabel = new QLabel(this);
    _blockIdLabel->setText("blockId:");
    _blockIdEdit = new QLineEdit(this);
    blockIdLayout->addWidget(_blockIdLabel);
    blockIdLayout->addWidget(_blockIdEdit);

    QHBoxLayout *weightLayout = new QHBoxLayout;
    _weightLabel = new QLabel(this);
    _weightLabel->setText(" weight:");
    _weightEdit = new QLineEdit(this);
    weightLayout->addWidget(_weightLabel);
    weightLayout->addWidget(_weightEdit);

    _entryButton = new QPushButton(this);
    _entryButton->setText("添加到组");
    connect(_entryButton,SIGNAL(clicked()),this,SLOT(addGroup()));

    _exportButton = new QPushButton(this);
    _exportButton->setText("导出文件");
    connect(_exportButton,SIGNAL(clicked()),this,SLOT(exportJsonFile()));

    QLabel *pillar = new QLabel(this);
    pillar->setText("新建");
    pillar->setAlignment(Qt::AlignCenter);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addWidget(pillar);
    leftLayout->addStretch(1);
    leftLayout->addLayout(groupNameLayout);
    leftLayout->addLayout(groupIdLayout);
    leftLayout->addStretch(1);
    leftLayout->addLayout(blockIdLayout);
    leftLayout->addLayout(weightLayout);
    leftLayout->addStretch(1);
    leftLayout->addWidget(_exportButton);
    leftLayout->addWidget(_entryButton);

    QVBoxLayout* midLayout = new QVBoxLayout;
    _groupItemName = new QLabel(this);
    _groupItemName->setText("组成员");
    _groupItemName->setAlignment(Qt::AlignCenter);
    _itemList = new QListWidget(this);
    _deleteGroupItem = new QPushButton(this);
    connect(_deleteGroupItem,SIGNAL(clicked()),this,SLOT(deleteGroupItem()));
    _deleteGroupItem->setText("删除组成员");

    midLayout->addWidget(_groupItemName);
    midLayout->addWidget(_itemList);
    midLayout->addWidget(_deleteGroupItem);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    _groupListName = new QLabel(this);
    _groupListName->setText("组");
    _groupListName->setAlignment(Qt::AlignCenter);
    _groupList = new QListWidget(this);
    connect(_groupList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showGroupItems(QListWidgetItem*)));
    _deleteGroup = new QPushButton(this);
    _deleteGroup->setText("删除组");
    connect(_deleteGroup,SIGNAL(clicked()),this,SLOT(deleteGroup()));
    rightLayout->addWidget(_groupListName);
    rightLayout->addWidget(_groupList);
    rightLayout->addWidget(_deleteGroup);
//
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->addLayout(leftLayout);
    _mainLayout->addSpacing(2);
    _mainLayout->addLayout(midLayout);
    _mainLayout->addLayout(rightLayout);
}

void BlockGroupDialog::addGroup()
{
    QString groupName = _groupNameEdit->text();
    int groupId = _groupIdEdit->text().toInt();
    GroupData* groupData = findGroupItem(groupId);

    GroupItem* item = new GroupItem;
    item->setBlockId(_blockIdEdit->text().toInt());
    item->setProbability(_weightEdit->text().toFloat());
    item->setMaxValue(-1);
    item->setMinValue(-1);

    if(groupData == NULL)
    {
        GroupData* data = new GroupData;
        data->setName(groupName);
        data->setGroupId(groupId);
        addGroupItem(groupName,_groupIdEdit->text());
        data->addGroupItem(item);
        _groups.append(data);
        emit groupsSender(_groups);
    }
    else
    {

        groupData->addGroupItem(item);
        showItems(groupData);
    }

}
void BlockGroupDialog::addGroupItem(QString name,QString num)
{
    QString itemName = QString("Name: ")+name+QString("\n");
    QString itemId = QString("Id: ")+num;

    QListWidgetItem* listItem = new QListWidgetItem;
    listItem->setText(itemName+itemId);
    _groupList->addItem(listItem);

}
GroupData* BlockGroupDialog::findGroupItem(int id)
{
    for(int i = 0 ; i < _groups.size();i++)
    {
        if(_groups.at(i)->getGroupId() == id)
        {
            qDebug() << "find id!" << endl;
            return _groups.at(i);

        }
    }
    return NULL;
}

void BlockGroupDialog::showItems(GroupData* group)
{
    _itemList->clear();
    for(int i = 0; i < group->getGroupItems().size(); i++)
    {
        GroupItem* item = group->getGroupItems().at(i);
        addItem(item->getBlockId(),item->getProbability());
    }

}
void BlockGroupDialog::addItem(int blockId, float weight)
{

    QString id;
    QString w;
    QString idName = QString("BlockId :")+id.setNum(blockId);
    QString weightName = QString("Weight: ")+w.setNum(weight);
    QListWidgetItem* listItem = new QListWidgetItem;
    listItem->setText(idName+QString("\n")+weightName);
    _itemList->addItem(listItem);

}

void BlockGroupDialog::showGroupItems(QListWidgetItem* item)
{
    QString id = item->text().split("Id:").last();
    showItems(findGroupItem(id.toInt()));
    //显示当前组
    _groupNameEdit->setText(item->text().split("\n").first().split("Name: ").last());
    _groupIdEdit->setText(id);
}
void BlockGroupDialog::deleteGroup()
{
    QString id = _groupList->currentItem()->text().split("Id:").last();

    //_groupList->removeItemWidget(_groupList->currentItem());
    removeGroupIndex(id.toInt());
    delete _groupList->currentItem();
    _itemList->clear();
}
void BlockGroupDialog::deleteGroupItem()
{
    QString blockId = _itemList->currentItem()->text().split("\n").front().split("BlockId :").last();
    QString id = _groupList->currentItem()->text().split("Id:").last();
    int num =removeGroupItemIndex(findGroupItem(id.toInt()),blockId.toInt());
    qDebug() << "block ID is " << blockId;
    qDebug() << "remove id is " << num ;
    delete _itemList->currentItem();
}
int BlockGroupDialog::removeGroupIndex(int id)
{
    for(int i = 0 ; i < _groups.size();i++)
    {
        if(_groups.at(i)->getGroupId() == id)
        {
            _groups.removeAt(i);
            return i;

        }
    }
    return -1;
}
int BlockGroupDialog::removeGroupItemIndex(GroupData*data,int blockId)
{
    qDebug() <<"size:"<<data->getGroupItems().size() << endl;
    for(int i = 0 ; i < data->getGroupItems().size(); i++)
    {
        if(data->getGroupItems().at(i)->getBlockId() == blockId)
        {
            data->removeGroupitem(i);
            qDebug() <<"remove size:"<<data->getGroupItems().count() << endl;
            return i;

        }
    }
    return -1;
}

void BlockGroupDialog::exportJsonFile()
{
    QJsonDocument jsonDocument;
    QJsonObject global;
    QJsonArray array;
    QJsonObject obj;
    qDebug() <<" * "<<_groups.size() << endl;
    for(int i = 0 ; i < _groups.size(); i++)
    {

        _groups.at(i)->insertJsonObject(obj);
        array.insert(i,obj);
    }
    global.insert("ruleBlockGroups",array);
    jsonDocument.setObject(global);
    new ExportFile(jsonDocument,NULL);
}
//QVector<QString> BlockGroupDialog::getGroupIds()
//{
////    for(int i  = 0; i< _groups.size(); i++)
////    {

////        _groudIds.append(_groups.at(i)->getGroupId());
////    }
//}
QVector<GroupData*> BlockGroupDialog::getGroups()
{
    return _groups;
}
//QVector<GeneralBlock*> BlockGroupDialog::getGroupBlockRules()
//{
//    for(int i = 0 ; i < _groups.size(); i++)
//    {
//        _groupBlockRules += _groups.at(i)->getGroupBlockRules();
//    }
//}
