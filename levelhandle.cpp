/*#include "levelhandle.h"

LevelHandle::LevelHandle()
{
}

void LevelHandle::parserLevel(const char* fileDir)
{

    QFile fileLevel(fileDir);
    //读json文件
    if(!fileLevel.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Open failed." << std::endl;
        return;
    }

    QTextStream txtInput(&fileLevel);
    QString fileStr;

    fileStr = txtInput.readAll();
    //解析关卡文件
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(fileStr.toUtf8(), &json_error);

    if(json_error.error == QJsonParseError::NoError){
        if(parse_doucment.isObject())  {

            //解析行列数据
            QJsonObject obj = parse_doucment.object();
            _levelInfo->iCols = obj.take("cols").toInt();
            _levelInfo->iRows = obj.take("rows").toInt();
            _widgetBlocksHeight = _levelInfo->iRows*70+kBlockYOffset*2;
            //解析方块数据
            QJsonArray arrayBlocks = obj.take("initialBlocks").toArray();
            for (int i = 0; i < arrayBlocks.size(); i++) {
                QJsonValue blockIdValue = arrayBlocks.at(i);
                _levelInfo->blockIds.push_back(blockIdValue.toInt());
            }

            //解析装饰物数据
            QJsonArray arrayConstraints = obj.take("constraintSprites").toArray();
            //by cxue
            qDebug() << "arrayConstrains.size :" << arrayConstraints.size() << endl;
            for (int i = 0;  i< arrayConstraints.size(); i++) {
                QJsonObject constraintInfo = arrayConstraints.at(i).toObject();
                QString resName = constraintInfo.take("resource").toString();
                int xOffset = constraintInfo.take("xOffset").toInt();
                int yOffset = constraintInfo.take("yOffset").toInt();
                int offsetToTop = constraintInfo.take("iOffsetToTop").toInt();
                char chImageDir[200];
                sprintf(chImageDir,"%s/%s.png",kConstraintsDir,resName.toUtf8().data());
                qDebug()<< "chImageDir is " << chImageDir << endl;
                QFile file(chImageDir);
                if (file.exists()){
                    qDebug() << " yes the file is exit" << endl;
                    DragLabel * label = new DragLabel(ui->widgetBlocks);
                    label->show();
                    char chImageDir[200];
                    sprintf(chImageDir,"%s/%s",kConstraintsDir,resName.toUtf8().data());

                    label->m_strImageName = resName.toUtf8().data();
                    QPixmap pixMap(chImageDir);
                    label->setPixmap(pixMap);
                    label->setGeometry(xOffset,_widgetBlocksHeight - yOffset - pixMap.height(),pixMap.width(),pixMap.height());

                    _levelInfo->constraints.push_back(label);
                }
            }
        }
    }
    fileLevel.close();

}
 */
