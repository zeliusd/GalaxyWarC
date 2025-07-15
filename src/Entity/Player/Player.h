#ifndef PLAYER_H
#define PLAYER_H
#include "../../Position/Position.h"
#include "../Asteroid/Asteroid.h"
#include "../Bullet/Bullet.h"
#include "Entity/Entity.h"
#include <memory>

class Player : public Entity, public std::enable_shared_from_this<Player> {
private:
  int indiceActualInventario;
  std::shared_ptr<Position> position;
  float speed;
  float width, height;
  bool alive;
  int points;

public:
  Player(float x = 0, float y = 0);
  std::shared_ptr<Position> getPosition() const;
  void move(float dx, float dy) override;
  float getSpeed() const;
  int getPoints() const;

  float getX() const override;
  float getY() const override;
  float getWidth() const override;
  float getHeight() const override;

  void onCollision(Entity &another) override;

  void collideWith(Asteroid &asteroid) override;
  void collideWith(Player &player) override;
  void collideWith(Bullet &bullet) override;
  void collideWith(Boss &boss) override;

  void incrementScore(int points);
  std::shared_ptr<Bullet> shotBullet();
  bool isAlive() const override;
};

#endif
