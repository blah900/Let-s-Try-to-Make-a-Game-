#ifndef ENTITY_SUPERFOOD_H
#define ENTITY_SUPERFOOD_H
#include "Entity_Food.h"
class Entity_SuperFood : public Entity_Food
{
protected:
    int stepSpeed;
    int currentStep;
    int startScore;
public:
    Entity_SuperFood(int x, int y, int stepSpeed=2, int score=25);
    ~Entity_SuperFood();

    void step();
    void draw(QPainter *painter);
};

#endif // ENTITY_SUPERFOOD_H
