#include "Blocks/Bloque.h"
#include "GameController/GameController.h"
#include "GameView/GameView.h"
#include "GameView/View/AsteroidView/AsteroidView.h"
#include "GameView/View/PlayerView/PlayerView.h"
#include "Player/Player.h"
#include "raylib.h"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <vector>

void generarBloques(std::vector<std::shared_ptr<Entity>> &entidades,
                    std::vector<std::shared_ptr<View>> &vistas, int cantidad) {
  for (int i = 0; i < cantidad; ++i) {
    auto bloque =
        std::make_shared<Bloque>(rand() % 760 + 20, -(rand() % 500 + 100));
    entidades.push_back(bloque);
    vistas.push_back(std::make_shared<AsteroidView>(bloque));
  }
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(800, 600, "Gameplay");
  InitAudioDevice();
  SetTargetFPS(60);

  unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
  srand(seed);

  std::vector<std::shared_ptr<Entity>> entidades;
  std::vector<std::shared_ptr<View>> vistas;

  std::shared_ptr<Player> player = std::make_shared<Player>(420, 500);

  auto playerview = std::make_shared<PlayerView>(player);

  generarBloques(entidades, vistas, 40);

  entidades.push_back(player);
  vistas.push_back(std::make_shared<PlayerView>(player));
  auto vista = std::make_shared<GameView>(vistas);
  GameController controller(vista);

  while (!WindowShouldClose()) {

    if (player->isAlive()) {
      BeginDrawing();
      controller.update(entidades, player);
      vista->draw();
    }

    if (!player->isAlive()) {
      DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 150});

      DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2,
               screenHeight / 2 - 40, 40, RED);
      DrawText("Presiona ESC para salir",
               screenWidth / 2 - MeasureText("Presiona ESC para salir", 20) / 2,
               screenHeight / 2 + 10, 20, WHITE);
      EndDrawing();
    }
  }
  CloseAudioDevice();

  CloseWindow();
  return 0;
}
