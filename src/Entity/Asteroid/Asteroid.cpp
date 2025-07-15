#include "Asteroid.h"

Asteroid::Asteroid(float x, float y)
    : position(std::make_shared<Position>(x, y)), width(40), height(40),
      alive(true) {}

float Asteroid::getX() const { return position->x; }
float Asteroid::getY() const { return position->y; }
float Asteroid::getWidth() const { return width; }
float Asteroid::getHeight() const { return height; }

void Asteroid::onCollision(Entity &another) { another.collideWith(*this); }

void Asteroid::collideWith(Player &player) { this->alive = false; }
void Asteroid::collideWith(Asteroid &asteroid) { this->alive = false; }
void Asteroid::collideWith(Bullet &bullet) { this->alive = false; }
void Asteroid::collideWith(Boss &boss) { return; }

void Asteroid::move(float x, float y) {
  position->x = x;
  position->y += y;
}
bool Asteroid::isAlive() const { return alive; }
