#ifndef POSITION_H
#define POSITION_H

class Position {

public:
  float x, y, z;
  Position(float x, float y, float z);
  void move(float dx, float dy, float dz);
};
#endif
