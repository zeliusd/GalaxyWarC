
#ifndef INVENTARIO_H
#define INVENTARIO_H
#include "../Blocks/Bloque.h"
#include <memory>
#include <vector>

class Inventario {
private:
  std::vector<std::shared_ptr<Bloque>> bloques;

public:
  Inventario() = default;
  void addBlock(std::shared_ptr<Bloque> bloque);
  std::shared_ptr<Bloque> tirarBloque(int indice);
  bool vacio();
  int cantidadElementos();
};

#endif
