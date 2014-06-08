#ifndef ORNAMENTALWIDGET_H
#define ORNAMENTALWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QVector>
#include "globaldef.h"
#include <QDir>
#include <QFileInfoList>

class OrnamentalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrnamentalWidget(QWidget *parent = 0);
    bool findFiles(const char * path,QVector<QString> & imageNames);
    void loadImgtoListWidget(const char* path);
private:
    QListWidget* _listWidget;
    QLabel * _name;
    QVBoxLayout* _vboxLayout;
    QVector<QString> _images;
    QVector<QListWidgetItem*> _listItems;
signals:
    void doubleClicked(QListWidgetItem*);
public slots:

};

#endif // ORNAMENTALWIDGET_H
