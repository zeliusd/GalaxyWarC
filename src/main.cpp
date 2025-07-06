#include "Blocks/Bloque.h"
#include "GameController/GameController.h"
#include "GameView/GameView.h"
#include "Player/Player.h"
#include "raylib.h"

int main() {
  InitWindow(800, 600, "MCT GAME");
  SetTargetFPS(60);

  Player player("Jugador", 100);
  Bloque bloque("Tierra", "a");
  GameController controller;
  GameView view;

  while (!WindowShouldClose()) {
    controller.updatePlayer(player);
    view.draw(player);
  }

  CloseWindow();
  return 0;
}
