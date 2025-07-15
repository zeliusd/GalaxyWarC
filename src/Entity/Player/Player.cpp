#include "Player.h"
#include "Entity/Asteroid/Asteroid.h"

Player::Player(float x, float y) {
  this->indiceActualInventario = 0;
  this->position = std::make_shared<Position>(x, y);
  this->speed = 300.0f;
  this->width = 60;
  this->height = 60;
  this->points = 0;
  this->alive = true;
}

std::shared_ptr<Position> Player::getPosition() const { return position; }

void Player::move(float dx, float dy) { position->move(dx, dy); }

float Player::getSpeed() const { return speed; }

float Player::getX() const { return position->x; }
float Player::getY() const { return position->y; }
float Player::getWidth() const { return width; }
float Player::getHeight() const { return height; }

int Player::getPoints() const { return this->points; }

void Player::onCollision(Entity &another) { another.collideWith(*this); }

void Player::collideWith(Asteroid &asteroid) { this->alive = false; }
void Player::collideWith(Player &player) { return; }
void Player::collideWith(Bullet &bullet) {
  if (bullet.isPlayerBullet())
    return;
  this->alive = false;
}
void Player::collideWith(Boss &boss) { this->alive = false; }

std::shared_ptr<Bullet> Player::shotBullet() {
  return std::make_shared<Bullet>(this->position->x, this->position->y - 50,
                                  0.0f, -450.0f, shared_from_this());
}

void Player::incrementScore(int points) { this->points += points; }

bool Player::isAlive() const { return alive; }
