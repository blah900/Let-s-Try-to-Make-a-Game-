#ifndef ENTITY_H
#define ENTITY_H
#include "globalLib.h"
class Entity
{
protected:
    int x,y,dx,dy;
    bool toDelete;
    int type;
public:
    Entity();
    ~Entity();
    //Game Event
    virtual void step();
    virtual void draw(QPainter* painter);
    void set(int x, int y);

    void setForRemoval();
    bool isSetForRemoval();

    //Accessors
    int getType();
    int getX();
    int getY();
};


namespace EntityType{
enum{
    FOOD,
    SUPERFOOD,
    BADFOOD
};
}
#endif // ENTITY_H
