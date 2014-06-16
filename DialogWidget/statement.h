#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class Statement:public QDialog
{
    Q_OBJECT

public:
     Statement(QWidget* parent = 0);
     void init();
public slots:

signals:

private:
     QLabel* _contentLabel;
     QVBoxLayout* _mainLayout;
};

#endif
