#include "Blocks/Bloque.h"
#include "GameController/GameController.h"
#include "GameView/GameView.h"
#include "Player/Player.h"
#include "raylib.h"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <vector>

std::shared_ptr<Bloque> createBlock() {
  float x = static_cast<float>(rand() % 760 + 20);
  float y = -static_cast<float>(rand() % 500 + 100);
  return std::make_shared<Bloque>(x, y);
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(800, 600, "Gameplay");
  SetTargetFPS(60);

  unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
  srand(seed);

  std::vector<std::shared_ptr<Entity>> entidades;

  std::shared_ptr<Player> player = std::make_shared<Player>(420, 500);

  for (int i = 0; i < 15; ++i) {
    entidades.push_back(createBlock());
  }

  entidades.push_back(player);

  GameController controller;
  GameView view;

  while (!WindowShouldClose()) {
    if (player->isAlive())
      controller.update(entidades, player);
    else {
      DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 150});

      DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2,
               screenHeight / 2 - 40, 40, RED);
      DrawText("Presiona ESC para salir",
               screenWidth / 2 - MeasureText("Presiona ESC para salir", 20) / 2,
               screenHeight / 2 + 10, 20, WHITE);
    }
    view.draw(entidades, player);
  }

  CloseWindow();
  return 0;
}
