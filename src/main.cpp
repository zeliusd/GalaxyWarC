#include "GameController/GameController.h"
#include "GameView/GameView.h"
#include "Player/Player.h"
#include "raylib.h"

int main() {
  InitWindow(800, 600, "Juego MVC - Cuadrado Negro");
  SetTargetFPS(60);

  Player player("Jugador", 100);
  GameController controller;
  GameView view;

  while (!WindowShouldClose()) {
    controller.update(player);
    view.draw(player);
  }

  CloseWindow();
  return 0;
}
