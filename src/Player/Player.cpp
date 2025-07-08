#include "Player.h"

Player::Player(float x, float y) {
  this->inventario = std::make_unique<Inventario>();
  this->indiceActualInventario = 0;
  this->position = std::make_shared<Position>(x, y);
  this->speed = 200.0f;
  this->width = 40;
  this->height = 40;
  this->points = 0;
}

std::shared_ptr<Bloque> Player::tirarBloque(int indiceBloque) {
  return inventario->tirarBloque(indiceBloque);
}

int Player::cantidadObjetosEnInventario() {
  return inventario->cantidadElementos();
}

void Player::agarrarBloque(std::shared_ptr<Bloque> bloque) {
  inventario->addBlock(bloque);
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

void Player::collideWith(Bloque &bloque) { this->points++; }
void Player::collideWith(Player &player) { return; }

bool Player::isAlive() const { return alive; }
