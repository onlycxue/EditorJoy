#ifndef _EXPORTFILE_H
#define _EXPORTFILE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QJsonDocument>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>

class ExportFile
{
public:
    ExportFile(QJsonDocument document,QWidget *parent = 0);
private:

};

#endif
