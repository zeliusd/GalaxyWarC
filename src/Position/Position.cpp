#include "Position.h"
#include <iostream>

Position::Position(float x, float y) {
  this->x = x;
  this->y = y;
}
void Position::move(float dx, float dy) {
  x += dx;
  y += dy;
}
