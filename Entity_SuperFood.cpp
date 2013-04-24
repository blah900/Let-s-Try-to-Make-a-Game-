#include "Entity_SuperFood.h"

Entity_SuperFood::Entity_SuperFood(int x, int y, int stepSpeed, int score) : Entity_Food(x,y,score,score/5)
{
    type=EntityType::SUPERFOOD;
    this->stepSpeed=stepSpeed;
    currentStep=0;
    startScore=25;
}

void Entity_SuperFood::step()
{
    if(currentStep!=stepSpeed){
        currentStep++;
        return;
    }
    currentStep=0;
    score--;
    if(score==1){
        setForRemoval();
    }
}

void Entity_SuperFood::draw(QPainter *painter)
{
    QBrush brush = painter->brush();
    double multiplier=(score*1.0)/startScore;
    painter->setBrush(QBrush(QColor(0,0,255.0*multiplier,255.0*multiplier),Qt::Dense1Pattern));
    painter->drawRect(x*Graphics::WIDTH+Graphics::WIDTH/4,y*Graphics::HEIGHT+Graphics::HEIGHT/4,Graphics::WIDTH/2,Graphics::HEIGHT/2);
    painter->drawText(x*Graphics::WIDTH,(y+1)*Graphics::HEIGHT,QString::number(score));
    painter->setBrush(brush);
}
