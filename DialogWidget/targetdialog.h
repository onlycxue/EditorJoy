#ifndef _TARGETDIALOG_H
#define _TARGETDIGLOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "targetdata.h"

class TargetDialog : public QDialog
{
    Q_OBJECT
public:
    TargetDialog(QWidget* parent = 0);
    void init();
    void setCurrentData(TargetData* data);
    TargetData* getTatgetData();
signals:
    void Clicked(TargetData*);
public slots:
    void ClickedHandle();
private:

    QPushButton* _entryButton;
    QPushButton* _cancelButton;

    QLabel* _petSumLabel;
    QLineEdit* _petSumLineEdit;
    QLabel* _star1Label;
    QLineEdit* _star1LineEdit;
    QLabel* _star2Label;
    QLineEdit* _star2LineEdit;
    QLabel* _star3Label;
    QLineEdit* _star3LineEdit;

    TargetData* _data;


};

#endif
