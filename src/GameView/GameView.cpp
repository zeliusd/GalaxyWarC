#include "GameView.h"

void GameView::draw(const Player &player) {
  BeginDrawing();
  ClearBackground(BLUE);

  auto pos = player.getPosition();
  DrawRectangle(static_cast<int>(pos->x), static_cast<int>(pos->y), 40, 40,
                BLACK);

  DrawText("MCT", 10, 10, 20, WHITE);

  EndDrawing();
}
