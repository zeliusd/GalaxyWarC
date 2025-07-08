#include "GameView.h"
#include "../Blocks/Bloque.h"
#include "../Entity/Boss/Boss.h"
#include "../Entity/Bullet/Bullet.h"
#include "raylib.h"
#include <string>

void GameView::draw(const std::vector<std::shared_ptr<Entity>> &entities,
                    const std::shared_ptr<Player> &player) {
  BeginDrawing();
  ClearBackground(BLUE);

  drawPlayer(player);
  drawEntities(entities);

  for (const auto &entity : entities) {
    if (auto boss = std::dynamic_pointer_cast<Boss>(entity)) {
      drawBossHealthBar(*boss);
    }
  }
  std::string puntosTexto = "Puntos: " + std::to_string(player->getPoints()) +
                            " Entities: " + std::to_string(entities.size());
  DrawText(puntosTexto.c_str(), 10, 10, 20, WHITE);

  EndDrawing();
}

void GameView::drawPlayer(const std::shared_ptr<Player> &player) {
  float x = player->getX() - 40 / 2.0f;
  float y = player->getY() - 40 / 2.0f;
  DrawRectangle((int)x, (int)y, 40, 40, BLACK);
}

void GameView::drawEntities(
    const std::vector<std::shared_ptr<Entity>> &entities) {
  for (auto &entity : entities) {

    if (dynamic_cast<Bloque *>(entity.get())) {
      float x = entity->getX() - entity->getWidth() / 2.0f;
      float y = entity->getY() - entity->getHeight() / 2.0f;
      DrawRectangle((int)x, (int)y, entity->getWidth(), entity->getHeight(),
                    GREEN);
    }
    if (dynamic_cast<Bullet *>(entity.get())) {
      float x = entity->getX();
      float y = entity->getY();
      DrawCircle((int)x, (int)y, 10, YELLOW);
    }

    if (dynamic_cast<Boss *>(entity.get())) {
      float x = entity->getX() - entity->getWidth() / 2.0f;
      float y = entity->getY() - entity->getHeight() / 2.0f;
      DrawRectangle((int)x, (int)y, entity->getWidth(), entity->getHeight(),
                    RED);
    }
  }
}

void GameView::drawBossHealthBar(const Boss &boss) {
  float barWidth = 300;
  float barHeight = 20;
  float x = (GetScreenWidth() - barWidth) / 2;
  float y = 20;

  float healthRatio = (float)boss.getHealth() / boss.getMaxHealth();
  float healthWidth = barWidth * healthRatio;

  // Fondo de la barra
  DrawRectangle(x, y, barWidth, barHeight, DARKGRAY);

  // Barra de vida
  DrawRectangle(x, y, healthWidth, barHeight, RED);

  // Borde
  DrawRectangleLines(x, y, barWidth, barHeight, WHITE);
}
