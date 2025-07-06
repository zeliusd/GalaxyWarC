#include "GameController.h"
#include "raylib.h"

// GameController.cpp
void GameController::updatePlayer(Player &player) {
  const float velocidad = player.getSpeed() * GetFrameTime();

  float dx = 0, dy = 0;

  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    dx += velocidad;
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    dx -= velocidad;
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    dy += velocidad;
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    dy -= velocidad;

  player.move(dx, dy, 0);
}
