#include "ornamentalwidget.h"

OrnamentalWidget::OrnamentalWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(140,500);
    this->setMaximumSize(180,540);
    this->setMinimumSize(180,540);
    _listWidget = new QListWidget(this);
    _listWidget->resize(180,540);

//    _name = new QLabel(this);
//    _name->setText("装饰物信息:");

//    _vboxLayout = new QVBoxLayout(this);
//    _vboxLayout->addWidget(_name);
//    _vboxLayout->addWidget(_listWidget);
    loadImgtoListWidget(ConstraintsBasePath);
    connect(_listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                    this,SIGNAL(doubleClicked(QListWidgetItem*)));
}
void OrnamentalWidget::loadImgtoListWidget(const char* path)
{
    findFiles(path,_images);

    for(int i=0;i<_images.size();i++){
        QString strImageName = _images.at(i);
        char chImageDir[200];
        sprintf(chImageDir,"%s/%s",ConstraintsBasePath,strImageName.toUtf8().data());
        QListWidgetItem* lstItem = new QListWidgetItem(QIcon(chImageDir), strImageName,_listWidget);
        _listWidget->setIconSize(QSize(50,50));
        _listItems.append(lstItem);

    }
}

bool OrnamentalWidget::findFiles(const char * path,QVector<QString> & imageNames)
{

    QDir dir(path);
    if (!dir.exists())
        return false;
    dir.setFilter(QDir::Dirs|QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    int i=0;
    do{
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName()=="."|fileInfo.fileName()=="..")
        {
            i++;
            continue;
        }
        bool bisDir=fileInfo.isDir();
        if(bisDir)
        {
//            std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
//                                    .arg(fileInfo.fileName(),10).arg(fileInfo.path()))<<endl;
            findFiles(fileInfo.filePath().toUtf8().data(),imageNames);
        }else{
            imageNames.append(fileInfo.fileName());
        }
        i++;
    }while(i<list.size());

    return true;
}
