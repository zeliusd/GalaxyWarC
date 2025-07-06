#include "GameView.h"
#include "../Blocks/Bloque.h"
#include "raylib.h"
#include <string>

void GameView::draw(const std::vector<std::shared_ptr<Entity>> &entities,
                    const std::shared_ptr<Player> &player) {
  BeginDrawing();
  ClearBackground(BLUE);

  drawPlayer(player);
  drawBlocks(entities);

  std::string puntosTexto = "Puntos: " + std::to_string(player->getPoints());
  DrawText(puntosTexto.c_str(), 10, 10, 20, WHITE);

  EndDrawing();
}

void GameView::drawPlayer(const std::shared_ptr<Player> &player) {
  float x = player->getX() - 40 / 2.0f;
  float y = player->getY() - 40 / 2.0f;
  DrawRectangle((int)x, (int)y, 40, 40, BLACK);
}

void GameView::drawBlocks(
    const std::vector<std::shared_ptr<Entity>> &entities) {
  for (auto &entity : entities) {
    if (dynamic_cast<Bloque *>(entity.get())) {
      float x = entity->getX() - entity->getWidth() / 2.0f;
      float y = entity->getY() - entity->getHeight() / 2.0f;
      DrawRectangle((int)x, (int)y, entity->getWidth(), entity->getHeight(),
                    GREEN);
    }
  }
}
