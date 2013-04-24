#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "globalLib.h"
#include <QTime>


class SnakeGame
{
private:
    QTime timer;
    int width,height;
    int score;
    int time, gameRate;
    int entityUpdateTicker;
    int superFoodAmt;
    int gameState;
    bool wrapAround;
    bool tookAction;
    Snake* snakeHead;
    QVector<Entity*> entities;
public:
    SnakeGame(int width=20, int height=20);
    void setup();
    void clean();

    //Game Actions
    void step(QPainter* painter);
    void draw(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawScore(QPainter* painter);
    bool checkWallCollision();
    bool checkEmpty(int x, int y);

    //Game Handlers        
    void entityCreationHandler(int entityType, int x=-1, int y=-1);
    void wallCollisionHandler();
    void entityCollisionHandler(Entity* entity);
    void handleKeyPress(int keyCode);

    //Game Accessors
    int getWidth();
    int getHeight();
};

#endif // SNAKEGAME_H
