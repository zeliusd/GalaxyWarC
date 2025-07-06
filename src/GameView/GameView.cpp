#include "GameView.h"

void GameView::draw(const Player &player) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  auto pos = player.getPosition();
  DrawRectangle(static_cast<int>(pos->x), static_cast<int>(pos->y), 40, 40,
                BLACK);

  DrawText("Jugador (cuadro negro) con MVC", 10, 10, 20, GRAY);

  EndDrawing();
}
