#include "Player.h"
#include <memory>
#include <utility>
Player::Player(std::string nombre, int puntosVida) {
  nombre = nombre;
  puntosVida = puntosVida;
  inventario = std::make_unique<Inventario>();
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
