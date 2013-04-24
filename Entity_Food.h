#ifndef ENTITY_FOOD_H
#define ENTITY_FOOD_H
#include "Entity.h"
class Entity_Food : public Entity
{
protected:
    int score;
    int increase;
public:
    Entity_Food(int x, int y,int score=1, int increase=1);
    ~Entity_Food();
    virtual void draw(QPainter *painter);

    int getScore();
    int getIncrease();

};

#endif // ENTITY_FOOD_H
