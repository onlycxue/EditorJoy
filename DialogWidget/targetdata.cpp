#include "targetdata.h"

TargetData::TargetData()
{
    _petNum = 0;
    _star1Score = 0;
    _star2Score = 0;
    _star3Score = 0;
}
TargetData& TargetData::operator = (TargetData& data)
{
    _petNum = data._petNum;
    _star1Score = data._star1Score;
    _star2Score = data._star2Score;
    _star3Score = data._star3Score;
    return *this;
}
void TargetData::setPetNum(int num)
{
    _petNum = num;
}
int TargetData::getPetNum()
{
    return _petNum;
}
void TargetData::setStar1Score(int score)
{
    _star1Score = score;
}
int TargetData::getStar1Score()
{
    return _star1Score;
}
void TargetData::setStar2Score(int score)
{
    _star2Score = score;
}
int TargetData::getStar2Score()
{
    return _star2Score;
}
void TargetData::setStar3Score(int score)
{
    _star3Score = score;
}
int TargetData::getStar3Score()
{
    return _star3Score;
}
QJsonArray TargetData::exportJsonArray()
{
   QJsonArray targetsArray;
   QJsonObject getScore;
   getScore.insert("pillar",QString("com.king.petrescue.game.pillar.target.PRTargetScore"));
   getScore.insert("name",QString("PRTargetScore"));
   targetsArray.insert(0,getScore);

   QJsonObject getpets;
   getpets.insert("pillar",QString("com.king.petrescue.game.pillar.target.PRTargetPets"));
   getpets.insert("pillarName",QString("PRTargetPets"));
   getpets.insert("numPets",this->getPetNum());
   targetsArray.insert(1,getpets);

   QJsonObject getstars;
   getstars.insert("pillar",QString("com.king.petrescue.game.pillar.target.stars.PRTargetStars"));
   getstars.insert("pillarName",QString("PRTargetStars"));
   getstars.insert("star_1",this->getStar1Score());
   getstars.insert("star_2",this->getStar2Score());
   getstars.insert("star_3",this->getStar3Score());
   targetsArray.insert(2,getstars);
   return targetsArray;
}

