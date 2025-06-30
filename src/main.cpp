#include "../external/raylib/src/raylib.h"

int main() {
  InitWindow(800, 600, "Mi juego con raylib");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Hola Raylib desde tu repo", 190, 200, 20, DARKGRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
