#ifndef PLAYER_H
#define PLAYER_H
#include "../Blocks/Bloque.h"
#include "../Inventory/Inventario.h"
#include "../Position/Position.h"
#include <memory>
#include <string>

class Player {
private:
  std::string nombre;
  int puntosVida;
  std::unique_ptr<Inventario> inventario;
  int indiceActualInventario;
  std::shared_ptr<Position> position;
  float speed;

public:
  Player(std::string nombre, int puntosVida);
  int cantidadObjetosEnInventario();
  std::unique_ptr<Bloque> tirarBloque(int indiceBloque);
  void agarrarBloque(std::unique_ptr<Bloque> bloque);
  std::shared_ptr<Position> getPosition() const;
  void move(float dx, float dy, float dz);
  float getSpeed() const;
};

#endif
