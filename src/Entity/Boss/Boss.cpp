
#include "Boss.h"

Boss::Boss(float x, float y) {
  this->position = std::make_shared<Position>(x, y);
  this->speed = 300.0f;
  this->width = 180;
  this->height = 180;
  this->alive = true;
  this->health = 15;
  this->maxHealth = 15;
}

void Boss::move(float dx, float dy) { position->move(dx, dy); }

float Boss::getSpeed() const { return speed; }

float Boss::getX() const { return position->x; }
float Boss::getY() const { return position->y; }
float Boss::getWidth() const { return width; }
float Boss::getHeight() const { return height; }

int Boss::getHealth() const { return this->health; }
int Boss::getMaxHealth() const { return this->maxHealth; }
void Boss::onCollision(Entity &another) { another.collideWith(*this); }

void Boss::collideWith(Bloque &bloque) { this->alive = false; }
void Boss::collideWith(Player &player) { return; }
void Boss::collideWith(Bullet &bullet) {
  if (this->health == 0) {
    this->alive = false;
    return;
  }
  this->health--;
}
void Boss::collideWith(Boss &boss) { return; }

bool Boss::isAlive() const { return alive; }

void Boss::setSpeed(float speed) { this->speed = speed; }

std::vector<std::shared_ptr<Bullet>> Boss::shotBullets() {
  std::vector<std::shared_ptr<Bullet>> bullets;

  float x = this->getX();
  float y = this->getY();

  bullets.push_back(
      std::make_shared<Bullet>(x, y + 200, 0.0f, 300.0f, nullptr));

  bullets.push_back(
      std::make_shared<Bullet>(x - 100, y + 200, -150.0f, 300.0f, nullptr));

  bullets.push_back(
      std::make_shared<Bullet>(x + 100, y + 200, 150.0f, 300.0f, nullptr));

  return bullets;
}
