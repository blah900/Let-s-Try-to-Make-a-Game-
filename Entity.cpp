#include "Entity.h"

Entity::Entity()
{
    toDelete=false;
    x=-1;
    y=-1;
}

Entity::~Entity()
{
}

void Entity::step()
{
}

void Entity::draw(QPainter *painter)
{
}

void Entity::set(int x, int y)
{
    this->x=x;
    this->y=y;
}

void Entity::setForRemoval()
{
    toDelete=true;
}

bool Entity::isSetForRemoval()
{
    return toDelete;
}

int Entity::getType()
{
    return type;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}
