#include "backgrounddialog.h"

BackgroudDialog::BackgroudDialog(QWidget* parent):
    QDialog(parent)
{
    init();
}

void BackgroudDialog::init()
{

    QHBoxLayout* hlayout = new QHBoxLayout;

    _nameLabel = new QLabel(this);
    _nameLabel->setText("背景图片:");

    QString nameStr = "park1.png,park2.png,park3.png,park4.png,park5.png,park6.png";
    QStringList nameList = nameStr.split(",");
    _names = new QComboBox(this);
    _names->addItems(nameList);
    hlayout->addWidget(_nameLabel);
    hlayout->addWidget(_names);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    _scanButton = new QPushButton(this);
    _scanButton->setText("预览");
    connect(_scanButton,SIGNAL(clicked()),this,SLOT(scanHandle()));

    _entryButton = new QPushButton(this);
    _entryButton->setText("确定");
    connect(_entryButton,SIGNAL(clicked()),this,SLOT(entryHandle()));

    buttonLayout->addWidget(_scanButton);
    buttonLayout->addWidget(_entryButton);


    QVBoxLayout* globalLayout = new QVBoxLayout(this);
    globalLayout->addLayout(hlayout);
    globalLayout->addLayout(buttonLayout);

}

void BackgroudDialog::scanHandle()
{

    _imageName = _names->currentText();
    emit backgroundName(_imageName);
    qDebug() << "###########################" <<_imageName << endl;
}
void BackgroudDialog::entryHandle()
{
   scanHandle();
   this->close();
}
