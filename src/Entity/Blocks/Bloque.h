

#ifndef BLOQUE_H
#define BLOQUE_H

#include "Entity/Entity.h"
#include "Position/Position.h"
#include <memory>

class Bloque : public Entity {
private:
  std::shared_ptr<Position> position;
  float width, height;
  bool alive;

public:
  Bloque(float x = 0, float y = 0);

  float getX() const override;
  float getY() const override;
  float getWidth() const override;
  float getHeight() const override;

  void onCollision(Entity &another) override;
  void collideWith(Player &player) override;
  void collideWith(Bloque &bloque) override;
  void collideWith(Bullet &bullet) override;
  void collideWith(Boss &boss) override;

  void move(float x, float y) override;
  bool isAlive() const override;
};

#endif
