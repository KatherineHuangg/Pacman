#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <iostream>
#include <vector>
#include"PosDir.h"

#define HASWAY(x) (x == 0 || x == 1 || x == -1)
#define FOOD 1
#define ROAD 0
#define BIGFOOD -1

using namespace PD;
using namespace std;

class GameMap{
    public:
      GameMap();
      bool touchwall(const Position&,const Direction&);
      Direction nextDirection(const Position&, const Position&);
      int& operator[](const Position&);

    public:
      friend ostream& operator<<(ostream&, GameMap&);

    private:
      int shortestpath(const Position&, const Position&);
      Position validPos(Position);

    private:
      int height;
      int width;
      std::vector<vector<int>> map;
};

#endif
