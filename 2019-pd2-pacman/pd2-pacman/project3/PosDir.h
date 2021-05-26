#ifndef POSDIR_H
#define POSDIR_H
struct Position{
  Position(double _x = 0, double _y = 0);
  double x, y;

  bool operator==(const Position&) const;
  bool isOnLactticePt();
};
namespace PD{
  enum Direction{up, right, down, left, center};
}

#endif
