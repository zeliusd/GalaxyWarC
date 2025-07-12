#include "GameView.h"
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

GameView::~GameView() { UnloadTexture(backgroundTexture); }

void GameView::draw() {
  BeginDrawing();

  this->drawBackground();
  this->drawEntities();
  if (this->debug) {
    drawCollider();
  }
  EndDrawing();
}
void GameView::drawBackground() {
  ClearBackground(BLUE);
  DrawTexturePro(
      backgroundTexture,
      {0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height},
      {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0.0f,
      WHITE);
  this->drawEntities();
  std::string puntosTexto = " Entities: " + std::to_string(entities.size());
  DrawText(puntosTexto.c_str(), 10, 10, 20, WHITE);
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
