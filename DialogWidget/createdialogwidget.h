#ifndef _CREATEDIALOGWIDGET_H_
#define _CREATEDIALOGWIDGET_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "createdata.h"
#include <QComboBox>
#include "../Global/globaldef.h"

class CreateFile:public QDialog
{
    Q_OBJECT

public:
     CreateFile(QWidget* parent = 0);
     void init();
public slots:
     void entryHandle();
     void changeImage(QString name);
signals:
     void sendMsg(CreateData*);

private:
     QLabel* _rowLabel;
     QLabel* _columnLabel;
     QLabel* _backgroundLabel;

     QLabel* _imageView;

     QLineEdit* _rowEdit;
     QLineEdit* _columnEdit;
     QComboBox* _names;
     QString _imageName;

     QPushButton* _entryButton;
     QPushButton* _cancelButton;
     QVBoxLayout* _mainLayout;
     CreateData* _msg;
};

#endif
