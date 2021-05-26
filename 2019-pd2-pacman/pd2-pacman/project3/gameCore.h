#ifndef GAMECORE_H
#define GAMECORE_H

#include "Map.h"
#include "Creatures.h"
#include <vector>

using namespace std;

class GameCore{
public:
  GameCore();
  void initGameRound();
  void updateRound();
  void checkTerminate();
  Position getPacmanPos();
  vector<Position> getGhostsPos();
  vector<bool> isGhostScared();

  void nextDir(Direction);

  GameMap& getMap();

  bool isEnd();
  bool isDie();

  int getScore();

private:
  void moveToNext(Position&, Direction&);


private:
  GameMap map;
  Pacman pacman;
  Position lactticePos;
  vector<Ghost*> ghosts;
  vector<int> inCave;
  int releaseCount;

  bool end;
  bool die;

  int life;
  int score;

  Direction nextPacDir;
};

#endif
