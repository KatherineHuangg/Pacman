#include "PosDir.h"

Position::Position(double _x, double _y) : x(_x), y(_y){}

bool Position::operator==(const Position& pos) const{
  return x == pos.x && y == pos.y;
}

bool Position::isOnLactticePt(){
  double dx = x - (int)x;
  double dy = y - (int)y;

  if((dx < 0.001 || dx > 0.99) && (dy < 0.001 || dy > 0.99)){
      x = dx < 0.001 ? (int)x : (int)x + 1;
      y = dy < 0.001 ? (int)y : (int)y + 1;
      return true;
  }

  return false;
}
