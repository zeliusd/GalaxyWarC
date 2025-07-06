#include "Blocks/Bloque.h"
#include "GameController/GameController.h"
#include "GameView/GameView.h"
#include "Player/Player.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>

std::shared_ptr<Bloque> crearMonedaAleatoria() {
  float x = static_cast<float>(rand() % 760 + 20);
  float y = static_cast<float>(-(rand() % 700));
  return std::make_shared<Bloque>(x, y);
}

int main() {
  InitWindow(800, 600, " Gameplay ");
  SetTargetFPS(60);
  srand(static_cast<unsigned>(time(nullptr)));

  std::vector<std::shared_ptr<Entity>> entidades;

  std::shared_ptr<Player> player = std::make_shared<Player>(300, 300);

  for (int i = 0; i < 10; ++i) {
    entidades.push_back(crearMonedaAleatoria());
  }
  entidades.push_back(player);
  GameController controller;
  GameView view;

  while (!WindowShouldClose()) {
    controller.update(entidades, player);
    view.draw(entidades, player);
  }

  CloseWindow();
  return 0;
}
