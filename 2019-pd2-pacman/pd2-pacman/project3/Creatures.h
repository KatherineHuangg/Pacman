#ifndef CREATURES_H
#define CREATURES_H

#include"PosDir.h"
using namespace PD;
/*struct Position{
  Position(int _x = 0, int _y = 0);
  int x, y;

  bool operator==(const Position&);
};

enum Direction{up, right, down, left, center};
*/

class Creatures{
public:
  Position& getPosition();
  Direction& getDirection();

public:
  Position selfPos;
  Direction selfDir;

};

class Pacman: public Creatures{
public:
  Pacman();
  Pacman(Position);
};

class Ghost : public Creatures{
public:
  Ghost(const Position&);
  Position getPacmanPos();
  virtual Position getTermPos() = 0;
  void scare();
  void unscare();

  bool isScared();

protected:
  const Position& pacPos;
  int scareCount;
};

class Blinky: public Ghost{
public:
  Blinky(const Position&);
  Position getTermPos();
};

class Clyde: public Ghost{
public:
  Clyde(const Position&);
  Position getTermPos();
};

class Inky: public Ghost{
public:
  Inky(const Position&, const Position&, const Direction&);
  Position getTermPos();

private:
  const Position& blinkyPos;
  const Direction& pacDir;
};

class Pinky: public Ghost{
public:
  Pinky(const Position&, const Direction&);
  Position getTermPos();

private:
  const Direction& pacDir;
};

#endif
