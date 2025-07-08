#include "GameController.h"
#include "Blocks/Bloque.h"
#include "Entity/Entity.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>
void GameController::update(std::vector<std::shared_ptr<Entity>> &entities,
                            std::shared_ptr<Player> player) {
  const float velocidad = player->getSpeed() * GetFrameTime();

  float dx = 0, dy = 0;
  if (IsKeyDown(KEY_D))
    dx += velocidad;
  if (IsKeyDown(KEY_A))
    dx -= velocidad;
  if (IsKeyDown(KEY_S))
    dy += velocidad;
  if (IsKeyDown(KEY_W))
    dy -= velocidad;

  player->move(dx, dy);
  fallBlocksUpdate(entities);
  manageColission(entities);

  entities.erase(std::remove_if(entities.begin(), entities.end(),
                                [](const std::shared_ptr<Entity> &e) {
                                  return !e->isAlive();
                                }),
                 entities.end());
}

void GameController::fallBlocksUpdate(
    std::vector<std::shared_ptr<Entity>> &entities) {
  for (auto &entity : entities) {
    if (dynamic_cast<Bloque *>(entity.get()) != nullptr) {
      entity->move(entity->getX(), 100 * GetFrameTime());
    }
  }
}

Rectangle getEntityRectangle(const Entity &e) {
  return {e.getX() - e.getWidth() / 2.0f, e.getY() - e.getHeight() / 2.0f,
          e.getWidth(), e.getHeight()};
}

bool checkCollisionEntidad(const Entity &a, const Entity &b) {
  Rectangle r1 = getEntityRectangle(a);
  Rectangle r2 = getEntityRectangle(b);

  // 👇 Debug visual (opcional, quitar si ya lo hacés en la vista)
  DrawRectangleLines(r1.x, r1.y, r1.width, r1.height, RED);
  DrawRectangleLines(r2.x, r2.y, r2.width, r2.height, RED);

  return CheckCollisionRecs(r1, r2);
}

void GameController::manageColission(
    std::vector<std::shared_ptr<Entity>> &entities) {
  for (size_t i = 0; i < entities.size(); ++i) {
    for (size_t j = i + 1; j < entities.size(); ++j) {
      auto &a = entities[i];
      auto &b = entities[j];

      if (checkCollisionEntidad(*a, *b)) {
        std::cout << "Colisión entre: " << a->getX() << "," << a->getY()
                  << " y " << b->getX() << "," << b->getY() << std::endl;

        a->onCollision(*b);
        b->onCollision(*a);
      }
    }
  }
}
