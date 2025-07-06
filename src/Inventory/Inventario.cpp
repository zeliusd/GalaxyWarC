#include "Inventario.h"

std::shared_ptr<Bloque> Inventario::tirarBloque(int indiceBloque) {
  if (indiceBloque < 0 || indiceBloque >= bloques.size()) {
    return nullptr;
  }

  auto bloque = bloques[indiceBloque];
  bloques.erase(bloques.begin() + indiceBloque);
  return bloque;
}

void Inventario::addBlock(std::shared_ptr<Bloque> bloque) {
  bloques.push_back(bloque);
}

bool Inventario::vacio() { return bloques.empty(); }

int Inventario::cantidadElementos() { return bloques.size(); }
