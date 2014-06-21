#include "createdata.h"

CreateData::CreateData()
{

}
CreateData& CreateData::operator=(CreateData& other)
{
    _row = other._row;
    _column = other._column;
    _background = other._background;
    return *this;
}
void CreateData::setRow(int row)
{
    _row = row;
}
void CreateData::setColumn(int column)
{
    _column = column;
}
void CreateData::setBackground(QString image)
{
    _background = image;
}
int CreateData::getRow()
{
    return _row;
}
int CreateData::getColumn()
{
    return _column;
}
QString CreateData::getBackground()
{
    return _background;
}
void CreateData::insertObject(QJsonObject& object)
{
    object.insert("cols",_column);
    object.insert("rows",_row);
    object.insert("background",_background.split(".").front());
}
