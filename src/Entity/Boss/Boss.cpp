
#include "Boss.h"

Boss::Boss(float x, float y) {
  this->position = std::make_shared<Position>(x, y);
  this->speed = 300.0f;
  this->width = 180;
  this->height = 180;
  this->alive = true;
  this->health = 100;
  this->maxHealth = 100;
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
