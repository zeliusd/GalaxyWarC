#ifndef BULLET_H
#define BULLET_H

#include "../../Blocks/Bloque.h"
#include "../../Position/Position.h"
#include "../Entity.h"
#include <memory>

class Bullet : public Entity {
private:
  std::shared_ptr<Position> position;
  float width, height;
  bool alive;
  std::weak_ptr<Player> player;

public:
  Bullet(float x, float y, std::shared_ptr<Player> shooter);

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
