
#ifndef INVENTARIO_H
#define INVENTARIO_H
#include "../Blocks/Bloque.h"
#include <memory>
#include <vector>

class Inventario {
private:
  std::vector<std::unique_ptr<Bloque>> bloques;

public:
  Inventario() = default;
  void addBlock(std::unique_ptr<Bloque> bloque);
  std::unique_ptr<Bloque> tirarBloque(int indice);
  bool vacio();
  int cantidadElementos();
};

#endif
