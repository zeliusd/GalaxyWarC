#ifndef PLAYER_H
#define PLAYER_H
#include "../Blocks/Bloque.h"
#include "../Entity/Entity.h"
#include "../Inventory/Inventario.h"
#include "../Position/Position.h"
#include <memory>
#include <string>

class Player : public Entity {
private:
  std::unique_ptr<Inventario> inventario;
  int indiceActualInventario;
  std::shared_ptr<Position> position;
  float speed;
  float width, height;
  bool alive;

public:
  Player(float x = 0, float y = 0);
  int cantidadObjetosEnInventario();
  std::unique_ptr<Bloque> tirarBloque(int indiceBloque);
  void agarrarBloque(std::unique_ptr<Bloque> bloque);
  std::shared_ptr<Position> getPosition() const;
  void move(float dx, float dy);
  float getSpeed() const;

  float getX() const override;
  float getY() const override;
  float getWidth() const override;
  float getHeight() const override;

  void onCollision(Entity &another) override;
  bool isAlive() const override;
};

#endif
