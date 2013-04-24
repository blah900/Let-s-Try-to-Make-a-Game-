#ifndef SNAKE_H
#define SNAKE_H
#include "globalLib.h"
class Snake
{
public:
    int x,y,dx,dy;
    QVector<Snake*> body;
    Snake();
    ~Snake();

    //Game Events
    void step();
    void draw(QPainter* painter);
    void drawHead(QPainter* painter);
    void drawBody(QPainter* painter);
    void extend(int amt = 1);
    void setPosition(int x, int y);


    //Checks
    bool checkEmpty(int x, int y);
    bool checkSelfCollision();
    bool checkEntityCollision(Entity* entity);
};

#endif // SNAKE_H
