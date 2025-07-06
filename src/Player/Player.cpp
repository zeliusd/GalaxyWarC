#include "Player.h"

Player::Player(float x, float y) {
  this->inventario = std::make_unique<Inventario>();
  this->indiceActualInventario = 0;
  this->position = std::make_shared<Position>(x, y);
  this->speed = 150.0f;
  this->width = 40;
  this->height = 40;
}

std::unique_ptr<Bloque> Player::tirarBloque(int indiceBloque) {
  return inventario->tirarBloque(indiceBloque);
}

int Player::cantidadObjetosEnInventario() {
  return inventario->cantidadElementos();
}

void Player::agarrarBloque(std::unique_ptr<Bloque> bloque) {
  inventario->addBlock(std::move(bloque));
}

std::shared_ptr<Position> Player::getPosition() const { return position; }

void Player::move(float dx, float dy) { position->move(dx, dy); }

float Player::getSpeed() const { return speed; }

float Player::getX() const { return position->x; }
float Player::getY() const { return position->y; }
float Player::getWidth() const { return width; }
float Player::getHeight() const { return height; }

void Player::onCollision(Entity &another) {
  // Nada
}

bool Player::isAlive() const { return alive; }
