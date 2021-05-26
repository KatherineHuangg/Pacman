#include"Map.h"
#include <exception>
#include <iostream>
using namespace std;

GameMap::GameMap(){
  height=19;
  width=21;
  map = {{3, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 3}, \
        {4, -1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,- 1, 4}, \
        {4, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 4}, \
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}, \
        {4, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 4}, \
        {4, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 4}, \
        {4, 4, 4, 4, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 4, 4, 4, 4}, \
        {4, 4, 4, 4, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 4, 4, 4, 4}, \
        {4, 4, 4, 4, 1, 2, 1, 5, 5, 7, 5, 5, 1, 2, 1, 4, 4, 4, 4}, \
        {4, 4, 4, 4, 1, 1, 1, 5, 0, 0, 0, 5, 1, 1, 1, 4, 4, 4, 4}, \
        {4, 4, 4, 4, 1, 2, 1, 5, 5, 5, 5, 5, 1, 2, 1, 4, 4, 4, 4}, \
        {4, 4, 4, 4, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 4, 4, 4, 4}, \
        {4, 4, 4, 4, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 4, 4, 4, 4}, \
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 4}, \
        {4, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 4}, \
        {4, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4}, \
        {4, 2, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 4}, \
        {4, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 4}, \
        {4, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2 ,2 ,2 ,2 ,2 ,1, 4}, \
        {4, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1 ,-1, 4}, \
        {3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 ,4 ,4 ,4 ,4 ,4, 3}};

}

bool GameMap::touchwall(const Position& nowpos,const Direction& nowdir){
  Position frontpos=nowpos;
  int a;
  switch(nowdir){
    case 0: case 2:
      a=nowdir==0?-1:1;
      frontpos.y=(nowpos.y+a);
      break;
    case 1: case 3:
      a=nowdir==1?1:-1;
      frontpos.x=(nowpos.x+a);
      break;
  }
  if(!HASWAY((*this)[frontpos]))
    return true;
  return false;
}

int& GameMap::operator[](const Position& pos){
  return map[pos.y][pos.x];
}

Direction GameMap::nextDirection(const Position& nowPos, const Position& destination){
  Position dest = validPos(destination);
  Direction shortestDir = Direction::center;
  int length[4] = {-1, -1, -1, -1};

  if(nowPos == dest) return Direction::center;
  //if(!HASWAY(map[destination.y][destination.x])) return Direction::center;

  int t = map[nowPos.y][nowPos.x];
  map[nowPos.y][nowPos.x] = 4;
  for(int i = 0; i < 4; i++){
    int dx = 0, dy = 0;
    switch(i){
      case 0: case 2:
        dy = i - 1;
        break;
      case 1: case 3:
        dx = -(i - 2);
        break;
    }


    Position newPos(nowPos.x + dx, nowPos.y + dy);
    if(HASWAY((*this)[newPos])){
      length[i] = shortestpath(newPos, dest);
      if(shortestDir == Direction::center || length[i] < length[shortestDir])
        shortestDir = Direction(i);
    }
  }

  map[nowPos.y][nowPos.x] = t;
  return shortestDir;
}

int GameMap::shortestpath(const Position& nowpos,const Position& destination){
    vector<vector<int>> cango = map;
    cango[nowpos.y][nowpos.x] = 10;
    vector<vector<Position>> path = {{nowpos}};

    while(true){
        vector<vector<Position>> tempPath;
        for(auto p : path){
            Position pos = p.back();
            for(int i = 0; i < 4; i++){
                int dx = 0, dy = 0;
                switch (i) {
                case 0: case 2:
                    dy = i - 1;
                    break;
                case 1: case 3:
                    dx = -(i - 2);
                    break;
                default:
                    break;
                }

                if(HASWAY(cango[pos.y + dy][pos.x + dx])){
                    Position tempPos(pos.x + dx, pos.y + dy);
                    if(tempPos == destination)
                        return p.size();

                    cango[tempPos.y][tempPos.x] = 10;
                    p.push_back(tempPos);
                    tempPath.push_back(p);
                    p.pop_back();
                }
            }
        }
        if(tempPath.size() == 0) return -1;

        path = tempPath;
    }
  /*static vector<vector<int>>cango=map;
  static int sp = -1;
  if(shortpath == -1)
    sp = -1;

  if(nowpos == destination){
    sp = shortpath;
    return 0;
  }

  if(sp >= 0 && shortpath >= sp)
    return -1;

  int pathLen = -1;
  cango[nowpos.y][nowpos.x] = 4; //have walked
  for(int i=0;i<4;i++){
    Position pos = nowpos;
    switch(i){
      case 0: case 2:
        pos.y= i==0?pos.y+1:pos.y-1;
        break;
      case 1: case 3:
        pos.x= i==1?pos.x+1:pos.x-1;
        break;
    }

    int temp = -1;
    if(HASWAY(cango[pos.y][pos.x]))
        temp = shortestpath(shortpath + 1, pos, destination);

    if(pathLen < 0)
      pathLen = temp;

    if(temp > 0 && temp < pathLen)
      pathLen = temp;
  }

  cango[nowpos.y][nowpos.x]= 1;
  return pathLen < 0 ? pathLen : pathLen + 1;*/

}

Position GameMap::validPos(Position pos){
    Position valid((int)pos.x, (int)pos.y);

    if(valid.x < 0) valid.x = 1;
    if(valid.x >= 19) valid.x = 17;
    if(valid.y < 0) valid.y = 1;
    if(valid.y >= 21) valid.y = 19;
    if(HASWAY(map[valid.y][valid.x])) return valid;

    int count = 1;
    while(true){
        for(int i = -count; i <= count; i++)
            for(int j = -count; j <= count; j++)
                try{
                    if(HASWAY(map.at(valid.y + i).at(valid.x + j))){
                        valid.x += j;
                        valid.y += i;
                        return valid;
                    }
                }catch(exception& e){}
        ++count;
    }
}

ostream& operator<<(ostream& out, GameMap& map){
  for(int i = 0; i < map.height; i++){
    for(int j = 0; j < map.width; j++){
      Position pos(i, j);
      out << map[pos] << " ";
    }

    out << endl;
  }

  return out;
}
