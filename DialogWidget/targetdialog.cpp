#include "targetdialog.h"

TargetDialog::TargetDialog(QWidget* parent):
    QDialog(parent)
{
    data = new TargetData;
    data->petNum = 0;
    data->star1Score = 0;
    data->star2Score = 0;
    data->star3Score = 0;
    init();
}

void TargetDialog::init()
{
    QHBoxLayout* petLineLayout = new QHBoxLayout;
    _petSumLabel = new QLabel(this);
    _petSumLabel->setText("宠物数量:");
    _petSumLineEdit = new QLineEdit(this);
    petLineLayout->addWidget(_petSumLabel);
    petLineLayout->addWidget(_petSumLineEdit);

    QHBoxLayout* star1LineLayout = new QHBoxLayout;
    _star1Label = new QLabel(this);
    _star1Label->setText("一星分数:");
    _star1LineEdit = new QLineEdit(this);
    star1LineLayout->addWidget(_star1Label);
    star1LineLayout->addWidget(_star1LineEdit);

    QHBoxLayout* star2LineLayout = new QHBoxLayout;
    _star2Label = new QLabel(this);
    _star2Label->setText("二星分数:");
    _star2LineEdit = new QLineEdit(this);
    star2LineLayout->addWidget(_star2Label);
    star2LineLayout->addWidget(_star2LineEdit);

    QHBoxLayout* star3LineLayout = new QHBoxLayout;
    _star3Label = new QLabel(this);
    _star3Label->setText("三星分数:");
    _star3LineEdit = new QLineEdit(this);
    star3LineLayout->addWidget(_star3Label);
    star3LineLayout->addWidget(_star3LineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    _entryButton = new QPushButton(this);
    _entryButton->setText("确定");
    connect(_entryButton,SIGNAL(clicked()),this,SLOT(ClickedHandle()));
    _cancelButton = new QPushButton(this);
    _cancelButton->setText("取消");
    connect(_cancelButton,SIGNAL(clicked()),this,SLOT(close()));

    buttonLayout->addWidget(_entryButton);
    buttonLayout->addWidget(_cancelButton);

    QVBoxLayout* globalLayout = new QVBoxLayout(this);
    globalLayout->addLayout(petLineLayout);
    globalLayout->addLayout(star1LineLayout);
    globalLayout->addLayout(star2LineLayout);
    globalLayout->addLayout(star3LineLayout);
    globalLayout->addLayout(buttonLayout);

}

void TargetDialog::ClickedHandle()
{
    data->petNum = _petSumLineEdit->text().toInt();
    data->star1Score = _star1LineEdit->text().toInt();
    data->star2Score = _star2LineEdit->text().toInt();
    data->star3Score = _star3LineEdit->text().toInt();
    this->close();
    emit Clicked(data);
}







