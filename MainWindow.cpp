#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(step()));
    timer->start(10);


}

void MainWindow::paintEvent(QPaintEvent *qpe)
{
    if(!updateRequired){
        return;
    }
    updateRequired=false;
    QPainter p;
    p.begin(this);
    game.step(&p);
    p.end();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_A||e->key()==Qt::Key_Left){
        game.handleKeyPress(Actions::LEFT);
    }else if(e->key()==Qt::Key_D||e->key()==Qt::Key_Right){
        game.handleKeyPress(Actions::RIGHT);
    }else if(e->key()==Qt::Key_W||e->key()==Qt::Key_Up){
        game.handleKeyPress(Actions::UP);
    }else if(e->key()==Qt::Key_S||e->key()==Qt::Key_Down){
        game.handleKeyPress(Actions::DOWN);
    }else if(e->key()==Qt::Key_Space){
        game.handleKeyPress(Actions::PAUSE);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step()
{
    updateRequired=true;
    update();

}
