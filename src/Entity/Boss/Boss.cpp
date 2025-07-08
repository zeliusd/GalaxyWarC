
#include "Boss.h"

Boss::Boss(float x, float y) {
  this->position = std::make_shared<Position>(x, y);
  this->speed = 300.0f;
  this->width = 100;
  this->height = 600;
  this->alive = true;
  this->lives = 100;
}

void Boss::move(float dx, float dy) { position->move(dx, dy); }

float Boss::getSpeed() const { return speed; }

float Boss::getX() const { return position->x; }
float Boss::getY() const { return position->y; }
float Boss::getWidth() const { return width; }
float Boss::getHeight() const { return height; }

int Boss::getLives() const { return this->lives; }

void Boss::onCollision(Entity &another) { another.collideWith(*this); }

void Boss::collideWith(Bloque &bloque) { this->alive = false; }
void Boss::collideWith(Player &player) { return; }
void Boss::collideWith(Bullet &bullet) { this->lives--; }
void Boss::collideWith(Boss &boss) { return; }

std::shared_ptr<Bullet> Boss::shotBullet() {
  auto bullet = std::make_shared<Bullet>(
      this->position->x, this->position->y - 2, shared_from_this());

  return bullet;
}

bool Boss::isAlive() const { return alive; }
