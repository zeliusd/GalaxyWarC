#include "Inventario.h"

std::unique_ptr<Bloque> Inventario::tirarBloque(int indiceBloque) {
  if (indiceBloque < 0 || indiceBloque >= bloques.size()) {
    return nullptr;
  }

  auto bloque = std::move(bloques[indiceBloque]);
  bloques.erase(bloques.begin() + indiceBloque);
  return bloque;
}

void Inventario::addBlock(std::unique_ptr<Bloque> bloque) {
  bloques.push_back(std::move(bloque));
}

bool Inventario::vacio() { return bloques.empty(); }

int Inventario::cantidadElementos() { return bloques.size(); }
