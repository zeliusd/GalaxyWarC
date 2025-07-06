#include "Bloque.h"
#include "../Player/Player.h"
Bloque::Bloque(float x, float y)
    : position(std::make_shared<Position>(x, y)), width(20), height(20),
      alive(true) {}

float Bloque::getX() const { return position->x; }
float Bloque::getY() const { return position->y; }
float Bloque::getWidth() const { return width; }
float Bloque::getHeight() const { return height; }

void Bloque::onCollision(Entity &otra) {
  if (dynamic_cast<Player *>(&otra) != nullptr) {
    alive = false;
  }
}

void Bloque::move(float x, float y) {
  position->x = x;
  position->y += y;
}
bool Bloque::isAlive() const { return alive; }
