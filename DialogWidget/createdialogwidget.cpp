#include "createdialogwidget.h"

CreateFile::CreateFile(QWidget* parent):
    QDialog(parent)
{
     _msg = new CreateData;
    init();

}
void CreateFile::init()
{
    QHBoxLayout* hrowLayout = new QHBoxLayout;
    _rowLabel = new QLabel(this);
    _rowLabel->setText("行数: ");
    _rowEdit = new QLineEdit(this);
    hrowLayout->addWidget(_rowLabel);
    hrowLayout->addWidget(_rowEdit);

    QHBoxLayout* hcolumnLayout = new QHBoxLayout;
    _columnLabel = new QLabel(this);
    _columnLabel->setText("列数: ");
    _columnEdit = new QLineEdit(this);
    hcolumnLayout->addWidget(_columnLabel);
    hcolumnLayout->addWidget(_columnEdit);

    QHBoxLayout* hlayout = new QHBoxLayout;

    _backgroundLabel = new QLabel(this);
    _backgroundLabel->setText("背景:");

    QString nameStr = "park1.png,park2.png,park3.png,park4.png,park5.png,park6.png";
    QStringList nameList = nameStr.split(",");

    _names = new QComboBox(this);
    _names->addItems(nameList);
    connect(_names,SIGNAL(activated(QString)),this,SLOT(changeImage(QString)));
    hlayout->addWidget(_backgroundLabel);
    hlayout->addWidget(_names);
    hlayout->setStretch(1,2);


    QHBoxLayout* hImageLayout = new QHBoxLayout;
    _imageView = new QLabel;
    QPixmap pixmap(":/images/Backgrounds/park1.png");
    pixmap.scaled(64,96,Qt::KeepAspectRatio);
    _imageView->setScaledContents(true);
    _imageView->setPixmap(pixmap);
    _imageView->setMinimumSize(64,96);
    _imageView->setMaximumSize(64,96);
    hImageLayout->addSpacing(1);
    hImageLayout->addWidget(_imageView);
    _msg->setBackground(":/images/Backgrounds/park1.png");

    QHBoxLayout* hbuttonLayout = new QHBoxLayout;
    _entryButton = new QPushButton(this);
    _entryButton->setText("确定");
    connect(_entryButton,SIGNAL(clicked()),this,SLOT(entryHandle()));

    _cancelButton = new QPushButton(this);
    _cancelButton->setText("取消");
    connect(_cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    hbuttonLayout->addWidget(_entryButton);
    hbuttonLayout->addWidget(_cancelButton);

    _mainLayout = new QVBoxLayout(this);
    _mainLayout->addLayout(hrowLayout);
    _mainLayout->addLayout(hcolumnLayout);
    _mainLayout->addLayout(hlayout);
    _mainLayout->addLayout(hImageLayout);
    _mainLayout->addLayout(hbuttonLayout);

}

void CreateFile::entryHandle()
{
    int rows = _rowEdit->text().toInt();
    int columns = _columnEdit->text().toInt();
//    if((0< rows && rows < 20)&&(0 < columns && columns < 20))
//    {

       _msg->setColumn(columns);
       _msg->setRow(rows);
//       _msg->setBackground(_names->currentText());
       emit sendMsg(_msg);
////       this->deleteLater();
//    }
//    else
//    {
//        //打印错误信息
//    }


}
void CreateFile::changeImage(QString name)
{
    QString imagePath = BackGroundBasePath+QString("/")+name;
    QPixmap pixmap(imagePath);
    pixmap.scaled(64,96,Qt::KeepAspectRatio);
    _imageView->setScaledContents(true);
    _imageView->setPixmap(pixmap);
    _msg->setBackground(imagePath);
}
