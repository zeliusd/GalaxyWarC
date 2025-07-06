#include "Position.h"

Position::Position(float x, float y, float z) {
  x = x;
  y = y;
  z = z;
}
void Position::move(float dx, float dy, float dz) {
  x += dx;
  y += dy;
  z += dz;
}
