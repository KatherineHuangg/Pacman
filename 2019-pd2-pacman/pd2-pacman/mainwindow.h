#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QtGui>

#include "project3/gameCore.h"
#include "project3/PosDir.h"

#include "project3/Map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void checkIsEnd();
    void updateCreatures();
    void updateFoods();

    void keyPressEvent(QKeyEvent*);

private slots:
    void update();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    QPushButton* foods[19][21];
    QPushButton* bg;
    QPushButton* pacman;
    QPushButton* ghosts[4];
    QLabel* scoreboard;

    GameCore core;
    int stopTime;
};

#endif // MAINWINDOW_H
