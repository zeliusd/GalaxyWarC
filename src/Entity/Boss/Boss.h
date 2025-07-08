
#ifndef BOSS_H
#define BOSS_H
#include "../../Blocks/Bloque.h"
#include "../../Position/Position.h"
#include "../Bullet/Bullet.h"
#include "../Entity.h"
#include <memory>

class Boss : public Entity {
private:
  std::shared_ptr<Position> position;
  float speed;
  float width, height;
  bool alive;
  int health;
  int maxHealth;

public:
  Boss(float x = 0, float y = 0);
  std::shared_ptr<Position> getPosition() const;
  void move(float dx, float dy) override;
  float getSpeed() const;
  int getPoints() const;

  float getX() const override;
  float getY() const override;
  float getWidth() const override;
  float getHeight() const override;

  void onCollision(Entity &another) override;
  void collideWith(Boss &boss) override;
  void collideWith(Bloque &bloque) override;
  void collideWith(Player &player) override;
  void collideWith(Bullet &bullet) override;
  void incrementScore(int points);
  std::shared_ptr<Bullet> shotBullet();
  bool isAlive() const override;

  int getHealth() const;
  int getMaxHealth() const;
};

#endif
