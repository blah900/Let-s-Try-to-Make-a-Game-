#include "Snake.h"
#include "Entity.h"
Snake::Snake()
{
    x=0;
    y=-1;
    dx=0;
    dy=1;
}

Snake::~Snake()
{
    //Destroy all the body segments.
    for(int i=0; i < body.size(); i++){
        delete body[i];
    }
}

void Snake::step()
{
    //Something to keep track of previous positions
    int prevX,prevY,prevXtemp,prevYtemp;
    prevX=x;
    prevY=y;

    x+=dx;
    y+=dy;

    for(int i=0; i<body.size(); i++){
        prevXtemp = body[i]->x;
        prevYtemp = body[i]->y;
        body[i]->setPosition(prevX,prevY);
        prevX=prevXtemp;
        prevY=prevYtemp;
    }

}

void Snake::draw(QPainter *painter)
{
    drawHead(painter);
    for(int i=0; i<body.size(); i++){
        body[i]->drawBody(painter);
    }
}

void Snake::drawHead(QPainter *painter)
{
    QBrush prevBrush= painter->brush();
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(x*Graphics::WIDTH,y*Graphics::HEIGHT,Graphics::WIDTH,Graphics::HEIGHT);
    painter->setBrush(prevBrush);
}

void Snake::drawBody(QPainter *painter)
{
    QBrush prevBrush= painter->brush();
    painter->setBrush(Qt::green);
    painter->drawRect(x*Graphics::WIDTH,y*Graphics::HEIGHT,Graphics::WIDTH,Graphics::HEIGHT);
    painter->setBrush(prevBrush);
}

void Snake::extend(int amt)
{
    //There really is no use calling extend if nothing is being extended so...
    if(amt<1){
        amt = 1;
    }
    for(int i=0; i<amt; i++){
        body.append(new Snake());
    }

}

void Snake::setPosition(int x, int y)
{
    this->x=x;
    this->y=y;
}

bool Snake::checkEmpty(int x, int y)
{
    if(this->x==x && this->y==y){
        return false;
    }

    for(int i=0; i<body.size(); i++){
        if(!body[i]->checkEmpty(x,y)){
            return false;
        }
    }
    return true;
}

bool Snake::checkSelfCollision()
{
    for(int i=0; i<body.size(); i++){
        if(body[i]->x==x && body[i]->y==y){
            return true;
        }
    }
    return false;
}

bool Snake::checkEntityCollision(Entity *entity)
{
    if(entity->getX()==x && entity->getY()==y){
        return true;
    }
    return false;
}
