#include "GameView.h"
#include "raylib.h"
#include <algorithm>
#include <string>
extern unsigned char space1_png[];
extern unsigned int space1_png_len;

GameView::GameView(std::vector<std::shared_ptr<View>> &entities)
    : entities(entities) {
  Image backgroundImage =
      LoadImageFromMemory(".png", space1_png, space1_png_len);
  backgroundTexture = LoadTextureFromImage(backgroundImage);
  UnloadImage(backgroundImage);
}

GameView::~GameView() {
  for (auto view : this->entities) {
    view->unloadTexture();
  }
  UnloadTexture(backgroundTexture);
}

void GameView::draw() {
  BeginDrawing();

  this->checkAlive();
  this->drawBackground();
  this->drawEntities();
  if (this->debug) {
    drawCollider();
  }

  std::string puntosTexto = " Entities: " + std::to_string(entities.size());
  DrawText(puntosTexto.c_str(), 10, 10, 20, WHITE);
  EndDrawing();
}
void GameView::drawBackground() {
  ClearBackground(BLUE);

  DrawTexturePro(
      backgroundTexture,
      {0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height},
      {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0.0f,
      WHITE);
}

void GameView::drawEntities() {

  for (auto &view : this->entities) {
    view->draw();
  }
}

void GameView::addView(std::shared_ptr<View> view) {
  this->entities.push_back(view);
}

void GameView::drawCollider() {

  for (auto &entity : this->entities) {
    DrawRectangleLines(entity->getReference()->getX() -
                           entity->getReference()->getWidth() / 2.0f,
                       entity->getReference()->getY() -
                           entity->getReference()->getHeight() / 2.0f,
                       entity->getReference()->getWidth(),
                       entity->getReference()->getHeight(), RED);
  }
}

void GameView::checkAlive() {
  entities.erase(std::remove_if(entities.begin(), entities.end(),
                                [](const std::shared_ptr<View> &e) {
                                  return !e->isAlive();
                                }),
                 entities.end());
}

void GameView::drawGameOver() {
  BeginDrawing();
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();
  DrawRectangle(0, 0, screenWidth, screenHeight, Color{0, 0, 0, 150});

  DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2,
           screenHeight / 2 - 40, 40, RED);
  DrawText("Presiona ESC para salir",
           screenWidth / 2 - MeasureText("Presiona ESC para salir", 20) / 2,
           screenHeight / 2 + 10, 20, WHITE);
  EndDrawing();
}

bool DrawButton(Button btn, int fontSize, Color idleColor, Color hoverColor,
                Color textColor) {
  Vector2 mouse = GetMousePosition();
  bool hovered = CheckCollisionPointRec(mouse, btn.bounds);

  DrawRectangleRec(btn.bounds, hovered ? hoverColor : idleColor);
  DrawText(btn.text, btn.bounds.x + 10,
           btn.bounds.y + btn.bounds.height / 2 - (float)fontSize / 2,
           (float)fontSize, textColor);

  return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

GameState GameView::drawMenu() {
  BeginDrawing();
  Button playButton = {{300, 200, 200, 50}, "PLAY"};
  Button exitButton = {{300, 270, 200, 50}, "EXIT"};

  DrawText("Galaxy War C++", 280, 100, 30, WHITE);

  if (DrawButton(playButton, 20, DARKGRAY, GRAY, WHITE)) {
    return GameState::PLAYING;
  }

  if (DrawButton(exitButton, 20, DARKGRAY, GRAY, WHITE)) {
    return GameState::EXIT;
  }
  EndDrawing();

  return GameState::MENU;
}
