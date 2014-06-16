#include "statement.h"

Statement::Statement(QWidget* parent):
    QDialog(parent)
{
    init();
}
void Statement::init()
{
    QString content = "本产品属于宠物消消乐的关卡编辑.\n@胡莱游戏";
    _contentLabel = new QLabel(this);
    _contentLabel->setText(content);
    _contentLabel->setAlignment(Qt::AlignCenter);
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->addWidget(_contentLabel);
}
