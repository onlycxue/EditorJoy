#ifndef _CREATEDIALOGWIDGET_H_
#define _CREATEDIALOGWIDGET_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

typedef struct
{
    int _rows;
    int _columns;

}DialogMsg;


class CreateFile:public QDialog
{
    Q_OBJECT

public:
     CreateFile(QWidget* parent = 0);
     void init();
public slots:
     void entryHandle();
signals:
     void sendMsg(DialogMsg*);
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
