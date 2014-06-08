#include "createdialogwidget.h"

CreateFile::CreateFile(QWidget* parent):
    QDialog(parent)
{
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

      QHBoxLayout* hbuttonLayout = new QHBoxLayout;
      _entryButton = new QPushButton(this);
      _entryButton->setText("确定");
      _cancelButton = new QPushButton(this);
      _cancelButton->setText("取消");
      hbuttonLayout->addWidget(_entryButton);
      hbuttonLayout->addWidget(_cancelButton);

      _mainLayout = new QVBoxLayout(this);
      _mainLayout->addLayout(hrowLayout);
      _mainLayout->addLayout(hcolumnLayout);
      _mainLayout->addLayout(hbuttonLayout);

}
