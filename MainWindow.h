#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globalLib.h"
#include "SnakeGame.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    SnakeGame game;
    QTimer* timer;

    void paintEvent(QPaintEvent *qpe);
    void keyPressEvent(QKeyEvent *e);
    ~MainWindow();

private slots:
    void step();
private:
    Ui::MainWindow *ui;
    bool updateRequired;
};

#endif // MAINWINDOW_H
