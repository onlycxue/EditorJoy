#include"exportfile.h"

ExportFile::ExportFile(QJsonDocument document,QWidget *parent)
{
    QByteArray content = document.toJson();
    qDebug() << content << endl;

    QString fileName = QFileDialog::getSaveFileName(parent,QString::null,"./Export","Text files (*.json)");
    if (fileName.length()>5) {
        QFile fileWrite( fileName.toUtf8().data() );
        fileWrite.open(QIODevice::WriteOnly);
        QTextStream streamSave(&fileWrite);
        streamSave<<content;
        fileWrite.close();
    }
}
