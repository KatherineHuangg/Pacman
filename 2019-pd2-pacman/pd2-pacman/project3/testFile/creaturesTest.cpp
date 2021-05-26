#include "../Creatures.h"
#include <iostream>
#include <string>

using namespace std;

void test(string, bool(*)());
string isPass(bool);

template <typename T1, typename T2>
bool isEqual(T1 t1, T2 t2){
    return t1 == t2;
}


int main(){

  test("PosCtorTest", [] () {
    Position pos(3, 4);
    return isEqual(pos.x, 3) && isEqual(pos.y, 4);
  });


  test("PacmanCtorPosTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);

    return isEqual(pos, pac.getPosition());
  });


  test("PacmanCtorDirTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);

    return isEqual(pac.getDirection(), Direction::center);
  });


  test("BlinkyCtorTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);
    Blinky bli(pac.getPosition());

    return isEqual(bli.getPacmanPos(), pac.getPosition());
  });


  test("ispacPosReference", [] () {
    Position pos(3, 4);
    Pacman pac(pos);
    Blinky bli(pac.getPosition());

    pac.selfPos.x = 10;

    return isEqual(bli.getPacmanPos().x, 10);
  });


  test("blinkyTermPosTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);
    Blinky bli(pac.getPosition());

    return isEqual(bli.getTermPos(), pac.getPosition());
  });


  test("ClydeCtorTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);
    Clyde cly(pac.getPosition());

    pac.selfPos.x = 11;

    return isEqual(cly.getPacmanPos().x, 11);
  });


  test("ClydeTermPosTest_1", [] () {
    Position pos(6, 8);
    Pacman pac(pos);
    Clyde cly(pac.getPosition());
    cly.selfPos = Position(0, 0);

    return isEqual(cly.getTermPos(), pac.getPosition());
  });


  test("ClydeTermPosTest_2", [] () {
    Position pos(3, 4), termPos(-10, -10);
    Pacman pac(pos);
    Clyde cly(pac.getPosition());
    cly.selfPos = Position(0, 0);

    return isEqual(cly.getTermPos(), termPos);
  });


  test("InkyCtorTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);
    Blinky bli(pac.getPosition());
    bli.selfPos = Position(0, 0);
    Inky inky(pac.getPosition(), bli.getPosition(), pac.getDirection());

    pac.selfPos.x = 0;

    return isEqual(inky.getPacmanPos().x, 0);
  });


  test("InkyTermPosTest", [] () {
    Position pos(3, 4), termPos(6, 12);
    Pacman pac(pos);
    Blinky bli(pac.getPosition());
    bli.selfPos = Position(0, 0);
    Inky inky(pac.getPosition(), bli.getPosition(), pac.getDirection());

    pac.selfDir = Direction::up;

    return isEqual(inky.getTermPos(), termPos);
  });


  test("PinkyCtorTest", [] () {
    Position pos(3, 4);
    Pacman pac(pos);
    Pinky pink(pac.getPosition(), pac.getDirection());

    pac.selfPos.x = 9;

    return isEqual(pink.getPacmanPos().x, 9);
  });


  test("PinkyTermPosTest", [] () {
    Position pos(3, 4), termPos(3, 2);
    Pacman pac(pos);
    Pinky pink(pac.getPosition(), pac.getDirection());

    pac.selfDir = Direction::down;

    return isEqual(pink.getTermPos(), termPos);
  });
  return 0;
}

void test(string testName, bool (*func)()){
  cout << testName << ": " << isPass(func()) << endl;
}

string isPass(bool pass){
  return pass ? "PASS" : "FAIL";
}
