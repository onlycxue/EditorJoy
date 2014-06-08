#ifndef _CREATEDIALOGWIDGET_H_
#define _CREATEDIALOGWIDGET_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


class  CreateFile:public QDialog
{
public:
     CreateFile(QWidget* parent = 0);
     void init();
private:
     QLabel* _rowLabel;
     QLabel* _columnLabel;
     QLineEdit* _rowEdit;
     QLineEdit* _columnEdit;

     QPushButton* _entryButton;
     QPushButton* _cancelButton;
     QVBoxLayout* _mainLayout;
};

#endif
