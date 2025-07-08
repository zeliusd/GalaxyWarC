#include "Bloque.h"

Bloque::Bloque(float x, float y)
    : position(std::make_shared<Position>(x, y)), width(20), height(20),
      alive(true) {}

float Bloque::getX() const { return position->x; }
float Bloque::getY() const { return position->y; }
float Bloque::getWidth() const { return width; }
float Bloque::getHeight() const { return height; }

void Bloque::onCollision(Entity &another) { another.collideWith(*this); }

void Bloque::collideWith(Player &player) { this->alive = false; }
void Bloque::collideWith(Bloque &bloque) { return; }

void Bloque::move(float x, float y) {
  position->x = x;
  position->y += y;
}
bool Bloque::isAlive() const { return alive; }
