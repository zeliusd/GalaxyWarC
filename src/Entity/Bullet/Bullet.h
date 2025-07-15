#ifndef BULLET_H
#define BULLET_H

#include "../../Position/Position.h"
#include "../Asteroid/Asteroid.h"
#include "../Entity.h"
#include <memory>

class Bullet : public Entity {
private:
  std::shared_ptr<Position> position;
  float width, height;
  bool alive;
  std::weak_ptr<Player> player;
  float vx = 0.0f;
  float vy = 0.0f;

public:
  Bullet(float x, float y, float vx, float vy, std::shared_ptr<Player> shoter);

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

  bool isPlayerBullet() const;
};

#endif
