#include "../Map.h"
#include "Tester.h"

int main(){

  test("TouchWallTest", [] () {
    GameMap map;

    Position curPos(1, 1);
    PD::Direction curDir1 = PD::Direction::up;
    PD::Direction curDir2 = PD::Direction::right;

    Assert::isTrue(map.touchwall(curPos, curDir1));
    Assert::isFalse(map.touchwall(curPos, curDir2));
  });

  test("NextDirectionTest", [] () {
    GameMap map;

    Position startPos(12, 7);
    Position termPos(9, 11);

    PD::Direction nextDir = map.nextDirection(startPos, termPos);

    Assert::isEqual(nextDir, PD::Direction::down);
  });

  test("Operator[]Test", [] () {
    GameMap map;

    Position testPos1(0, 0), testPos2(1, 1);

    Assert::isFalse(HASWAY(map[testPos1]));
    Assert::isTrue(HASWAY(map[testPos2]));
  });

  return 0;
}
