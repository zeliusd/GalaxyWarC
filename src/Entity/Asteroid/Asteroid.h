

#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity/Entity.h"
#include "Position/Position.h"
#include <memory>

class Asteroid : public Entity {
private:
  std::shared_ptr<Position> position;
  float width, height;
  bool alive;

public:
  Asteroid(float x = 0, float y = 0);

  float getX() const override;
  float getY() const override;
  float getWidth() const override;
  float getHeight() const override;

  void onCollision(Entity &another) override;
  void collideWith(Player &player) override;
  void collideWith(Asteroid &asteroid) override;
  void collideWith(Bullet &bullet) override;
  void collideWith(Boss &boss) override;

  void move(float x, float y) override;
  bool isAlive() const override;
};

#endif
