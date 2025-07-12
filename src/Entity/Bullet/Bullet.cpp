#include "Bullet.h"
#include "../../Entity/Player/Player.h"
Bullet::Bullet(float x, float y, float vx, float vy,
               std::shared_ptr<Player> shoter)
    : position(std::make_shared<Position>(x, y)), width(35), height(35),
      alive(true), vx(vx), vy(vy), player(shoter) {}

float Bullet::getX() const { return position->x; }
float Bullet::getY() const { return position->y; }
float Bullet::getWidth() const { return width; }
float Bullet::getHeight() const { return height; }

void Bullet::onCollision(Entity &another) { another.collideWith(*this); }

void Bullet::collideWith(Bullet &bullet) { this->alive = false; }
void Bullet::collideWith(Player &player) {}
void Bullet::collideWith(Boss &boss) { this->alive = false; }

void Bullet::collideWith(Bloque &bloque) {
  this->alive = false;

  if (auto p = player.lock()) {
    p->incrementScore(1);
  }
}

void Bullet::move(float x, float y) {
  position->x += vx * x;
  position->y += vy * x;
}

bool Bullet::isPlayerBullet() const { return !this->player.expired(); }
bool Bullet::isAlive() const { return alive; }
