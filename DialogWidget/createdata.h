#ifndef _CREATEDATA_H_
#define _CREATEDATA_H_
#include <QString>
#include <QJsonObject>
#include <QStringList>

class CreateData
{
public:
    CreateData();
    CreateData& operator=(CreateData& other);
    void setRow(int row);
    void setColumn(int column);
    void setBackground(QString image);

    int getRow();
    int getColumn();
    QString getBackground();
    void insertObject(QJsonObject& object);

private:
    int _row;
    int _column;
    QString _background;
};


#endif
