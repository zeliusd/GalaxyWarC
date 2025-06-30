#ifndef PLAYER_H
#define PLAYER_H
#include "../Blocks/Bloque.h"
#include "../Inventory/Inventario.h"
#include <memory>
#include <string>

class Player {
private:
  std::string nombre;
  int puntosVida;
  std::unique_ptr<Inventario> inventario;

public:
  Player(std::string nombre, int puntosVida);
  int cantidadObjetosEnInventario();
  std::unique_ptr<Bloque> tirarBloque(int indiceBloque);
  void agarrarBloque(std::unique_ptr<Bloque> bloque);
};

#endif
