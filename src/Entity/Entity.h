
#ifndef ENTIDAD_H
#define ENTIDAD_H

class Entity {
public:
  virtual float getX() const = 0;
  virtual float getY() const = 0;
  virtual float getWidth() const = 0;
  virtual float getHeight() const = 0;

  virtual void onCollision(Entity &otra) = 0;
  virtual void collideWith(class Player &player) = 0;
  virtual void collideWith(class Bloque &block) = 0;

  virtual bool isAlive() const = 0;
  virtual void move(float x, float y) = 0;
  virtual ~Entity() = default;
};

#endif
