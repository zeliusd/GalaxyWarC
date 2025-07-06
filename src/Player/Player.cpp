#include "Player.h"
#include "Position/Position.h"

Player::Player(std::string nombre, int puntosVida) {
  nombre = nombre;
  puntosVida = puntosVida;
  inventario = std::make_unique<Inventario>();
  indiceActualInventario = 0;
  position = std::make_shared<Position>(0, 0, 0);
  speed = 150.0f;
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

void Player::move(float dx, float dy, float dz) { position->move(dx, dy, dz); }

float Player::getSpeed() const { return speed; }
