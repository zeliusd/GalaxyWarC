#include "GameView.h"
#include "../Blocks/Bloque.h"
#include "../Player/Player.h"
#include "raylib.h"
void GameView::draw(const std::vector<std::shared_ptr<Entity>> &entities) {
  BeginDrawing();
  ClearBackground(BLUE);

  for (auto &entity : entities) {
    float x = entity->getX();
    float y = entity->getY();

    if (dynamic_cast<Player *>(entity.get())) {
      DrawRectangle((int)x, (int)y, 40, 40, BLACK);
    } else if (dynamic_cast<Bloque *>(entity.get())) {
      DrawRectangle((int)x, (int)y, entity->getWidth(), entity->getHeight(),
                    GREEN);
    } else {
      DrawRectangle((int)x, (int)y, (int)entity->getWidth(),
                    (int)entity->getHeight(), BLACK);
    }
  }

  DrawText("Movimiento: WASD.", 10, 10, 20, WHITE);

  EndDrawing();
}
