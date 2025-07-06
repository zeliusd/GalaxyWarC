#ifndef POSITION_H
#define POSITION_H

class Position {

public:
  float x, y;
  Position(float x, float y);
  void move(float dx, float dy);
};
#endif
