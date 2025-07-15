#include "Entity/Asteroid/Asteroid.h"
#include "Entity/Player/Player.h"
#include "GameController/GameController.h"
#include "GameView/GameView.h"
#include "GameView/View/AsteroidView/AsteroidView.h"
#include "GameView/View/PlayerView/PlayerView.h"
#include "raylib.h"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <vector>

void generateAsteroids(std::vector<std::shared_ptr<Asteroid>> &entidades,
                       std::vector<std::shared_ptr<View>> &vistas,
                       int cantidad) {
  for (int i = 0; i < cantidad; ++i) {
    auto asteroid =
        std::make_shared<Asteroid>(rand() % 760 + 20, -(rand() % 500 + 100));
    entidades.push_back(asteroid);
    vistas.push_back(std::make_shared<AsteroidView>(asteroid));
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

  std::vector<std::shared_ptr<Asteroid>> entidades;
  std::vector<std::shared_ptr<View>> vistas;

  std::shared_ptr<Player> player = std::make_shared<Player>(420, 500);

  auto playerview = std::make_shared<PlayerView>(player);

  generateAsteroids(entidades, vistas, 40);

  vistas.push_back(std::make_shared<PlayerView>(player));
  auto vista = std::make_shared<GameView>(vistas);
  GameController controller(vista, player, entidades);

  while (!WindowShouldClose() && !controller.gameExit()) {
    controller.update();
  }
  CloseAudioDevice();

  CloseWindow();
  return 0;
}
