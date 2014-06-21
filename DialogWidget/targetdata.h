#ifndef _TARGETDATA_H_
#define _TARGETDATA_H_
#include <QJsonObject>
#include <QJsonArray>

class TargetData
{
public:

    TargetData();
    TargetData& operator = (TargetData& data);
    void setPetNum(int num);
    int getPetNum();
    void setStar1Score(int score);
    int getStar1Score();
    void setStar2Score(int score);
    int getStar2Score();
    void setStar3Score(int score);
    int getStar3Score();
    QJsonArray exportJsonArray();

private:
   int _petNum;
   int _star1Score;
   int _star2Score;
   int _star3Score;
};
#endif
