#include "Bullet.h"
#include "../../Player/Player.h"

Bullet::Bullet(float x, float y, std::shared_ptr<Player> shooter)
    : position(std::make_shared<Position>(x, y)), width(20), height(20),
      alive(true), player(shooter) {}

float Bullet::getX() const { return position->x; }
float Bullet::getY() const { return position->y; }
float Bullet::getWidth() const { return width; }
float Bullet::getHeight() const { return height; }

void Bullet::onCollision(Entity &another) { another.collideWith(*this); }

void Bullet::collideWith(Bullet &bullet) {}
void Bullet::collideWith(Player &player) {}
void Bullet::collideWith(Boss &boss) { this->alive = false; }

void Bullet::collideWith(Bloque &bloque) {
  this->alive = false;

  if (auto p = player.lock()) {
    p->incrementScore(1);
  }
}

void Bullet::move(float x, float y) {
  position->x = x;
  position->y += y;
}

bool Bullet::isAlive() const { return alive; }
