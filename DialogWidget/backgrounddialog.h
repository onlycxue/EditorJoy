#ifndef _BACKGROUNDDIALOG_H_
#define _BACKFROUNDDIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDebug>

class BackgroudDialog : public QDialog
{
    Q_OBJECT
public:
    BackgroudDialog(QWidget* parent = 0);
    void init();
signals:
    void backgroundName(QString);
public slots:
    void scanHandle();
    void entryHandle();
private:

    QPushButton* _entryButton;
    QPushButton* _scanButton;

    QLabel* _nameLabel;
    QComboBox* _names;
    QString _imageName;
};


#endif
