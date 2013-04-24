#ifndef GLOBALLIB_H
#define GLOBALLIB_H
#include <QVector>

#include <QPainter>
#include <QTimer>

#include <QDebug>
//Prime the classes that will be used everywhere.
class Snake;
class Entity;
class SnakeGame;


//Some constants to be defined
namespace GameState{
enum{
    RUNNING,
    PAUSED,
    GAMEOVER,
    WAITING
};
}

namespace Graphics{
enum{
    WIDTH=32,
    HEIGHT=32,
    MENU_WIDTH=150
};
}

namespace Actions{
enum{
    LEFT,
    UP,
    DOWN,
    RIGHT,
    PAUSE
};
}
#endif // GLOBALLIB_H
