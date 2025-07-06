#include "GameView.h"
#include "../Blocks/Bloque.h"
#include "raylib.h"
void GameView::draw(const std::vector<std::shared_ptr<Entity>> &entities,
                    const std::shared_ptr<Player> &player) {
  BeginDrawing();
  ClearBackground(BLUE);

  drawPlayer(player);
  for (auto &entity : entities) {
    float x = entity->getX();
    float y = entity->getY();

    if (dynamic_cast<Bloque *>(entity.get())) {
      DrawRectangle((int)x, (int)y, entity->getWidth(), entity->getHeight(),
                    GREEN);
    }
  }

  DrawText("Movimiento: WASD.", 10, 10, 20, WHITE);

  EndDrawing();
}

void GameView::drawPlayer(const std::shared_ptr<Player> &player) {
  DrawRectangle((int)player->getX(), (int)player->getY(), 40, 40, BLACK);
}
