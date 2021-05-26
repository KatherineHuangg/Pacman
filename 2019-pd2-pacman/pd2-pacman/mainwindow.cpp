#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    core.initGameRound();

    scoreboard = new QLabel(this);
    scoreboard->setGeometry(810, 300, 100, 100);
    scoreboard->setText("0");

    bg = new QPushButton(this);
    bg->setGeometry(0, 0, 808, 902);
    bg->setIcon(QIcon("../Pacman/pacmanmap.jpg"));
    bg->setIconSize(QSize(808, 902));

    pacman = new QPushButton(this);
    pacman->setIconSize(QSize(30, 30));
    pacman->setStyleSheet("border: 0ptx;");
    pacman->setIcon(QIcon("../Pacman/Pacman.png"));

    for(int i = 0; i < 4; i++){
        ghosts[i] = new QPushButton(this);
        ghosts[i]->setStyleSheet("border: 0ptx;");
        ghosts[i]->setIconSize(QSize(30, 30));
    }

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 21; j++){
            foods[i][j] = new QPushButton(this);
            foods[i][j]->setGeometry(i*42.5, j*43, 42.5, 43);
            foods[i][j]->setIconSize(QSize(20, 20));
            foods[i][j]->setStyleSheet("border: 0ptx;");
        }
    }

    stopTime = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(75);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    PD::Direction dir = PD::Direction::center;
    switch (event->key()) {
        case Qt::Key_W: case Qt::Key_Up:
            dir = PD::Direction::up;
            break;
        case Qt::Key_D: case Qt::Key_Right:
            dir = PD::Direction::right;
            break;
        case Qt::Key_S: case Qt::Key_Down:
            dir = PD::Direction::down;
            break;
        case Qt::Key_A: case Qt::Key_Left:
            dir = PD::Direction::left;
            break;
        default:
            break;
    }

    core.nextDir(dir);
}

void MainWindow::update(){
    core.updateRound();

    core.checkTerminate();

    checkIsEnd();
    updateFoods();
    updateCreatures();

    scoreboard->setText(to_string(core.getScore()).c_str());
}

void MainWindow::checkIsEnd(){
    if(core.isEnd()){
        timer->stop();
        return;
    }

    if(core.isDie()){
        core.initGameRound();
    }
}

void MainWindow::updateCreatures(){
    Position pacPos = core.getPacmanPos();
    pacman->setGeometry(pacPos.x*42.5, pacPos.y*43, 42.5, 43);

    vector<Position> ghostPos = core.getGhostsPos();
    vector<bool> scaredGhost = core.isGhostScared();

    vector<QString> path = {"../Pacman/BLINKY.png", "../Pacman/CLYDE.png", "../Pacman/INKY.png", "../Pacman/PINKY.png"};

    for(int i = 0; i < ghostPos.size(); i++){
        if(scaredGhost[i]) ghosts[i]->setIcon(QIcon("../Pacman/SCARE.png"));
        else ghosts[i]->setIcon(QIcon(path[i]));

        Position& pos = ghostPos[i];
        ghosts[i]->setGeometry(pos.x*42.5, pos.y*43, 42.5, 43);
    }

}

void MainWindow::updateFoods(){
    GameMap& gameMap = core.getMap();
    for(int i = 0; i < 19; i++)
        for(int j = 0; j < 21; j++){
            Position pos(i, j);

            switch (gameMap[pos]) {
            case FOOD:
                foods[i][j]->setIcon(QIcon("../Pacman/Food.png"));
                break;
            case BIGFOOD:
                foods[i][j]->setIcon(QIcon("../Pacman/Food.png"));
                foods[i][j]->setIconSize(QSize(30, 30));
                break;
            default:
                foods[i][j]->setIcon(QIcon(""));
                break;
            }
        }
}

MainWindow::~MainWindow(){
    delete ui;
}
