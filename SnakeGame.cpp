#include "SnakeGame.h"
#include "Snake.h"
#include "Entity.h"
#include "Entity_Food.h"
#include "Entity_SuperFood.h"
SnakeGame::SnakeGame(int width, int height)
{

    //Set the dimensions of the snake grid.
    this->width=width;
    this->height=height;
    snakeHead=0;
    setup();
}

void SnakeGame::setup()
{
    clean();
    timer.start();
    score=0;
    time=0;
    entityUpdateTicker=0;
    this->gameRate=150;
    snakeHead = new Snake();
    snakeHead->extend(3);
    this->gameState=GameState::PAUSED;
    entityCreationHandler(EntityType::FOOD,width/2,height/2);    
    superFoodAmt=0;
    tookAction=false;

}

void SnakeGame::clean()
{
    if(snakeHead!=0){
     delete snakeHead;
    }
    for(int i=0; i<entities.size(); i++){
        delete entities[i];
    }
    entities.clear();

}

void SnakeGame::step(QPainter *painter)
{    
    //Gamerate determines how fast the game passes

    drawBackground(painter);
    if(gameState == GameState::RUNNING && (timer.elapsed() > gameRate || tookAction)){
        time+=timer.elapsed();
        entityUpdateTicker+=timer.elapsed();
        timer.start();
        //Move the snake
        snakeHead->step();

        //Check the wall collision first (The order of collision detection does matter)
        if(checkWallCollision()){
            wallCollisionHandler();
        }

        //Check if the new position causes a self collision
        if(snakeHead->checkSelfCollision()){
            gameState=GameState::GAMEOVER;
        }

        //Move the entities or whatever they do. If they collide, send it to collision detection handler.
        //Also flag the entities that are set for removal
        //Entity shouldn't be affected by keyboard events so have a updateEntity boolean
        bool updateEntity=false;
        if(entityUpdateTicker>gameRate){
            updateEntity=true;
            entityUpdateTicker=0;
        }
        for(int i=0; i<entities.size(); i++){            
            if(updateEntity){
                entities[i]->step();
            }
            if(snakeHead->checkEntityCollision(entities[i])){
                entityCollisionHandler(entities[i]);
            }
        }

        QVector<Entity*>::iterator i;
        for(i=entities.begin(); i!=entities.end(); i++){
            if((*i)->isSetForRemoval()){                
                delete (*i);
                i=entities.erase(i);                                
            }
            if(i==entities.end()){
                break;
            }
        }
        tookAction=false;
    }
    draw(painter);
    if(gameState == GameState::PAUSED){
        painter->setFont(QFont("Times",20));
        painter->drawText(0,0,width*Graphics::WIDTH,height*Graphics::HEIGHT,Qt::AlignCenter,"Press Space to Unpause!");
    }else if(gameState== GameState::GAMEOVER){
        painter->setFont(QFont("Times",20));
        painter->drawText(0,0,width*Graphics::WIDTH,height*Graphics::HEIGHT,Qt::AlignCenter,"GAME OVER! PRESS SPACE TO TRY AGAIN!");
    }
    drawScore(painter);
}

void SnakeGame::draw(QPainter *painter)
{
    snakeHead->draw(painter);
    for(int i=0; i<entities.size(); i++){
        entities[i]->draw(painter);
    }
}

void SnakeGame::drawBackground(QPainter *painter)
{
    QBrush brush = painter->brush();
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            if(i%2==1){
                if(j%2==1){
                    painter->setBrush(Qt::white);
                }else{
                    painter->setBrush(Qt::lightGray);
                }
            }else{
                if(j%2==1){
                    painter->setBrush(Qt::lightGray);
                }else{
                    painter->setBrush(Qt::white);
                }

            }
            painter->drawRect(i*Graphics::WIDTH,j*Graphics::HEIGHT,Graphics::WIDTH,Graphics::HEIGHT);
        }
    }

    painter->setBrush(Qt::gray);
    painter->drawRect(width*Graphics::WIDTH,0,Graphics::MENU_WIDTH,height*Graphics::HEIGHT);
    painter->setBrush(brush);

}

void SnakeGame::drawScore(QPainter *painter)
{
    painter->setFont(QFont("Times",20));
    painter->drawText(width*Graphics::WIDTH,0,Graphics::MENU_WIDTH,height*Graphics::HEIGHT,Qt::AlignTop,"Score");
    painter->drawText(width*Graphics::WIDTH,25,Graphics::MENU_WIDTH,height*Graphics::HEIGHT,Qt::AlignTop,QString::number(score));
    painter->drawText(width*Graphics::WIDTH,50,Graphics::MENU_WIDTH,height*Graphics::HEIGHT,Qt::AlignTop,"Rate");
    painter->drawText(width*Graphics::WIDTH,75,Graphics::MENU_WIDTH,height*Graphics::HEIGHT,Qt::AlignTop,QString::number(gameRate));
    painter->drawText(width*Graphics::WIDTH,100,Graphics::MENU_WIDTH,height*Graphics::HEIGHT,Qt::AlignTop,"Elapsed:");
    painter->drawText(width*Graphics::WIDTH,125,Graphics::MENU_WIDTH,height*Graphics::HEIGHT,Qt::AlignTop,QString::number(time/1000));
}

bool SnakeGame::checkWallCollision()
{
    //It collided into the wall if it's in the negative coordinate or if the snake is beyond the boundaries of the game.
    if(snakeHead->x<0 || snakeHead->x>=width || snakeHead->y <0 || snakeHead->y >=height){
        return true;
    }
    return false;
}

bool SnakeGame::checkEmpty(int x, int y)
{
    if(!snakeHead->checkEmpty(x,y)){
        return false;
    }

    for(int i=0; i<entities.size(); i++){
        if(entities[i]->getX()==x && entities[i]->getY()==y){
            return false;
        }
    }
    return true;
}

void SnakeGame::entityCreationHandler(int entityType, int x, int y)
{
    if(x<0){
        x=rand()%width;
    }
    if(y<0){
        y=rand()%height;
    }
    while(!checkEmpty(x,y)){
        x=rand()%width;
        y=rand()%height;
    }

    if(entityType == EntityType::FOOD){                
        entities.append(new Entity_Food(x,y));
        if(rand()%50>45 && superFoodAmt<3){
            superFoodAmt++;
            entityCreationHandler(EntityType::SUPERFOOD);
        }
    }else if(entityType==EntityType::SUPERFOOD){
        entities.append(new Entity_SuperFood(x,y));
    }
}

void SnakeGame::wallCollisionHandler()
{
    //If wraparound is enabled, teleport to the other side
    if(wrapAround){
        //We add the width in case of negatives in which case -1 would become size-1, which gives us last edge of the board
        //Otherwise it would become (size+size)%size, which effectively gives us 0, the beginning edge of the board.
        snakeHead->setPosition((snakeHead->x+width)%width,(snakeHead->y+height)%height);
    }else{
        //GameOver
        gameState = GameState::GAMEOVER;
    }
}

void SnakeGame::entityCollisionHandler(Entity *entity)
{
    if(entity->getType()==EntityType::FOOD ||entity->getType()==EntityType::SUPERFOOD){
        Entity_Food* food = (Entity_Food*)entity;
        score+=food->getScore()*(150-gameRate)/3+food->getScore();
        snakeHead->extend(food->getIncrease());
        food->setForRemoval();
        if(entity->getType()==EntityType::FOOD){
            gameRate-=2;
            entityCreationHandler(EntityType::FOOD);
        }
        if(entity->getType()==EntityType::SUPERFOOD){
            gameRate-=5;
            superFoodAmt--;
        }

    }
}

void SnakeGame::handleKeyPress(int keyCode)
{    
    if(keyCode==Actions::LEFT && snakeHead->dx==0 && !tookAction){
        snakeHead->dx=-1;
        snakeHead->dy=0;
        tookAction=true;
    }else if(keyCode==Actions::RIGHT && snakeHead->dx==0 && !tookAction){
        snakeHead->dx=1;
        snakeHead->dy=0;
        tookAction=true;
    }else if(keyCode==Actions::UP && snakeHead->dy==0 && !tookAction){
        snakeHead->dx=0;
        snakeHead->dy=-1;
        tookAction=true;
    }else if(keyCode==Actions::DOWN && snakeHead->dy==0&& !tookAction){
        snakeHead->dx=0;
        snakeHead->dy=1;
        tookAction=true;
    }else if(keyCode==Actions::PAUSE){
        if(gameState==GameState::RUNNING){
            gameState=GameState::PAUSED;
        }else if(gameState==GameState::PAUSED){
            gameState=GameState::RUNNING;
        }else if(GameState::GAMEOVER){
            setup();
        }
    }
}

int SnakeGame::getWidth()
{
    return width;
}

int SnakeGame::getHeight()
{
    return height;
}
