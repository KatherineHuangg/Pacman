#include "gameCore.h"

GameCore::GameCore(){
  score = 0;
  life = 1;
  end = false;
}

void GameCore::initGameRound(){
    releaseCount = 30;
  die = false;
  Position pos(9, 11);
  Direction dir = Direction::center;
  pacman = Pacman(pos);
  pacman.selfDir = dir;

  lactticePos = pos;
  nextPacDir = dir;

  Ghost* ghost;

  pos = Position(9, 7);
  ghost = new Blinky(lactticePos);
  ghost->getPosition() = pos;
  ghost->selfDir = dir;
  ghosts.push_back(ghost);

  pos = Position(9, 9);
  ghost = new Clyde(lactticePos);
  ghost->getPosition() = pos;
  ghost->selfDir = dir;
  ghosts.push_back(ghost);

  pos = Position(8, 9);
  ghost = new Inky(lactticePos, ghosts[0]->getPosition(), pacman.getDirection());
  ghost->selfDir = dir;
  ghost->getPosition() = pos;
  ghosts.push_back(ghost);

  pos = Position(10, 9);
  ghost = new Pinky(lactticePos, pacman.getDirection());
  ghost->selfDir = dir;
  ghost->getPosition() = pos;
  ghosts.push_back(ghost);

  for(int i = 0; i < 4; i++)
      ghosts[i]->unscare();

  for(int i = 1; i < 4; i++)
      inCave.push_back(i);
}



void GameCore::updateRound(){
  if(pacman.getPosition().isOnLactticePt()){
    pacman.getDirection() = nextPacDir;
    lactticePos = pacman.getPosition();
    if(map[pacman.getPosition()] == FOOD){
        map[pacman.getPosition()] = ROAD;
        score++;
    }else if(map[pacman.getPosition()] == BIGFOOD){
        map[pacman.getPosition()] = ROAD;
        for(auto& ghost : ghosts)
            ghost->scare();
    }
  }
  moveToNext(pacman.getPosition(), pacman.getDirection());

  if(inCave.size() != 0 && releaseCount-- <= 0){
      ghosts[inCave.at(0)]->getPosition() = Position(9, 7);
      inCave.erase(inCave.begin());
      releaseCount = 30;
  }

  for(int i = 0; i < ghosts.size(); i++){
    if(ghosts[i]->getPosition().isOnLactticePt())
        ghosts[i]->getDirection() = map.nextDirection(ghosts[i]->getPosition(), ghosts[i]->getTermPos());

    moveToNext(ghosts[i]->getPosition(), ghosts[i]->getDirection());
  }

  checkTerminate();
}

Position GameCore::getPacmanPos(){
  return pacman.getPosition();
}

vector<Position> GameCore::getGhostsPos(){
  vector<Position> posList;

  /*for(int i = 0; i < ghosts.size(); i++){
    posList.push_back(ghosts[i]->getPosition());
  }*/

  for(auto& ghost : ghosts)
    posList.push_back(ghost->getPosition());

  return posList;
}

vector<bool> GameCore::isGhostScared(){
    vector<bool> scare;
    for(auto& ghost : ghosts)
        scare.push_back(ghost->isScared());

    return scare;
}

void GameCore::nextDir(Direction dir){
  nextPacDir = dir;
}

GameMap& GameCore::getMap(){
  return map;
}

bool GameCore::isEnd(){
  return end;
}

bool GameCore::isDie(){
  return die;
}

int GameCore::getScore(){
    return score;
}

void GameCore::checkTerminate(){
  for(int i = 0; i < ghosts.size(); i++){
    auto& ghost = ghosts[i];
    Position& gPos = ghost->getPosition();
    Position& pPos = pacman.getPosition();

    double dx = gPos.x > pPos.x ? gPos.x - pPos.x : pPos.x - gPos.x;
    double dy = gPos.y > pPos.y ? gPos.y - pPos.y : pPos.y - gPos.y;

    if(dx < 0.5 && dy < 0.5){
        if(ghost->isScared()){
            ghost->getPosition() = Position(9, 9);
            ghost->unscare();
            inCave.push_back(i);
            score += 50;
        }else{
            die = true;
            life--;
            break;
        }
    }
  }

  if(life == 0)
    end = true;

}

void GameCore::moveToNext(Position& pos, Direction& dir){
  if(pos.isOnLactticePt()){
    if(map.touchwall(pos, dir))
      return;
  }

  double dx = 0, dy = 0;
  switch (dir) {
    case Direction::center:
      break;
    case Direction::up: case Direction::down:
      dy = 0.2*(dir - 1);
      break;
    case Direction::left: case Direction::right:
      dx = -0.2*(dir - 2);
      break;
  }

  pos.x += dx;
  pos.y += dy;
}
