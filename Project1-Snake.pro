#-------------------------------------------------
#
# Project created by QtCreator 2013-04-18T06:38:45
#
#-------------------------------------------------

QT       += core gui

TARGET = Project1-Snake
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Snake.cpp \
    SnakeGame.cpp \
    Entity.cpp \
    Entity_Food.cpp \
    Entity_SuperFood.cpp

HEADERS  += MainWindow.h \
    Snake.h \
    globalLib.h \
    SnakeGame.h \
    Entity.h \
    Entity_Food.h \
    Entity_SuperFood.h

FORMS    += MainWindow.ui
