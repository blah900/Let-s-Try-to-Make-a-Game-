#include "Entity_Food.h"

Entity_Food::Entity_Food(int x, int y, int score, int increase)
{
    this->x=x;
    this->y=y;
    this->type=EntityType::FOOD;
    this->score=score;
    this->increase=increase;
}

Entity_Food::~Entity_Food()
{
}

void Entity_Food::draw(QPainter *painter)
{
    QBrush brush = painter->brush();
    painter->setBrush(Qt::blue);
    painter->drawRect(x*Graphics::WIDTH+Graphics::WIDTH/4,y*Graphics::HEIGHT+Graphics::HEIGHT/4,Graphics::WIDTH/2,Graphics::HEIGHT/2);
    painter->setBrush(brush);
}

int Entity_Food::getScore()
{
    return score;
}

int Entity_Food::getIncrease()
{
    return increase;
}
