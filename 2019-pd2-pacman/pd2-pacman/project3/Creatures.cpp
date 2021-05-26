#include "Creatures.h"
#include <math.h>


Position& Creatures::getPosition(){
  return selfPos;
}

Direction& Creatures::getDirection(){
  return selfDir;
}

Pacman::Pacman(){}

Pacman::Pacman(Position initPos){
  selfPos = initPos;
  selfDir = Direction::center;
}


Ghost::Ghost(const Position& pacman) : pacPos(pacman) {
    scareCount = 0;
}

void Ghost::scare(){
    scareCount = 30;
}

void Ghost::unscare(){
    scareCount = 0;
}

bool Ghost::isScared(){
    return scareCount > 0;
}

Position Ghost::getPacmanPos(){
  return pacPos;
}

Blinky::Blinky(const Position& pacman) : Ghost(pacman) {}

Position Blinky::getTermPos(){
   if(scareCount > 0){
        Position pos(1, 1);
        scareCount--;
        return pos;
   }

  return pacPos;
}

Clyde::Clyde(const Position& pacman) : Ghost(pacman) {}

Position Clyde::getTermPos() {
    if(scareCount > 0){
         Position pos(1, 19);
         scareCount--;
         return pos;
    }

  if(sqrt( pow(pacPos.x,2)+pow(pacPos.y,2) )>=8){
    return pacPos;
  }
  else{
    return Position(1, 1);
  }


}


Inky::Inky(const Position& pacman, const Position& blinky, const Direction& dir) : Ghost(pacman), blinkyPos(blinky), pacDir(dir) {}

Position Inky::getTermPos() {
    if(scareCount > 0){
         Position pos(17, 1);
         scareCount--;
         return pos;
    }

  Position destination;
  switch(pacDir){
    case 0:
      destination.x=((pacPos.x)-blinkyPos.x)*2;
      destination.y=((pacPos.y+2)-blinkyPos.y)*2;
      break;
    case 1:
      destination.x=((pacPos.x+2)-blinkyPos.x)*2;
      destination.y=((pacPos.y)-blinkyPos.y)*2;
      break;
    case 2:
      destination.x=((pacPos.x)-blinkyPos.x)*2;
      destination.y=((pacPos.y-2)-blinkyPos.y)*2;
      break;
    case 3:
      destination.x=((pacPos.x-2)-blinkyPos.x)*2;
      destination.y=((pacPos.y)-blinkyPos.y)*2;
      break;
  }
  return destination;

}


Pinky::Pinky(const Position& pacman, const Direction& dir) : Ghost(pacman), pacDir(dir) {}

Position Pinky::getTermPos() {
    if(scareCount > 0){
         Position pos(17, 19);
         scareCount--;
         return pos;
    }

  int a;
  Position destination=pacPos;
  switch(pacDir){
    case 0: case 2:
      a= pacDir==0?2:-2;
      destination.y=pacPos.y+a;
      break;

    case 1: case 3:
      a= pacDir==1?2:-2;
      destination.x=pacPos.x+a;
      break;

  }
  return destination;
}
