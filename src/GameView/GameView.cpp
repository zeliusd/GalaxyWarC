#include "GameView.h"
#include "../Blocks/Bloque.h"
#include "../Entity/Boss/Boss.h"
#include "../Entity/Bullet/Bullet.h"
#include <iostream>
#include <string>

GameView::GameView() {
  playerTexture = LoadTexture("src/resources/nave.png");
  asteriodTexture = LoadTexture("src/resources/asteroid.png");
  backgroundTexture = LoadTexture("src/resources/space1.png");
  bossTexture = LoadTexture("src/resources/boss.png");
  if (asteriodTexture.id <= 0) {
    std::cerr << "ERROR: No se pudo cargar la textura nave.png\n";
  } else {
    std::cout << "Textura asteroid.png cargada correctamente.\n";
  }
}

GameView::~GameView() {
  UnloadTexture(playerTexture);
  UnloadTexture(asteriodTexture);
  UnloadTexture(backgroundTexture);
  UnloadTexture(bossTexture);
}

void GameView::draw(const std::vector<std::shared_ptr<Entity>> &entities,
                    const std::shared_ptr<Player> &player) {
  BeginDrawing();
  ClearBackground(BLUE);
  DrawTexturePro(
      backgroundTexture,
      {0, 0, (float)backgroundTexture.width,
       (float)backgroundTexture.height},                         // source
      {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, // destination
      {0, 0},                                                    // origin
      0.0f,                                                      // rotation
      WHITE                                                      // tint
  );
  drawPlayer(player);
  drawEntities(entities);

  for (const auto &entity : entities) {
    if (auto boss = std::dynamic_pointer_cast<Boss>(entity)) {
      drawBossHealthBar(*boss);
    }
  }
  std::string puntosTexto = "Puntos: " + std::to_string(player->getPoints()) +
                            " Entities: " + std::to_string(entities.size());
  DrawText(puntosTexto.c_str(), 10, 10, 20, WHITE);

  drawCollider(entities);
  EndDrawing();
}

void GameView::drawPlayer(const std::shared_ptr<Player> &player) {
  Rectangle source = {0, 0, (float)playerTexture.width,
                      (float)playerTexture.height};
  Rectangle dest = {player->getX() - player->getWidth() / 2.0f,
                    player->getY() - player->getHeight() / 2.0f,
                    player->getWidth(), player->getHeight()};
  Vector2 origin = {0, 0};
  DrawTexturePro(playerTexture, source, dest, origin, 0.0f, WHITE);
}

void GameView::drawEntities(
    const std::vector<std::shared_ptr<Entity>> &entities) {
  for (auto &entity : entities) {

    if (dynamic_cast<Bloque *>(entity.get())) {
      Rectangle source = {0, 0, (float)asteriodTexture.width,
                          (float)asteriodTexture.height};
      Rectangle dest = {entity->getX() - entity->getWidth() / 2.0f,
                        entity->getY() - entity->getHeight() / 2.0f,
                        entity->getWidth(), entity->getHeight()};
      Vector2 origin = {0, 0};
      DrawTexturePro(asteriodTexture, source, dest, origin, 0.0f, WHITE);
    }
    if (dynamic_cast<Bullet *>(entity.get())) {
      float x = entity->getX();
      float y = entity->getY();
      DrawCircle((int)x, (int)y, 10, YELLOW);
    }

    if (dynamic_cast<Boss *>(entity.get())) {
      Rectangle source = {0, 0, (float)bossTexture.width,
                          (float)bossTexture.height};
      Rectangle dest = {entity->getX() - entity->getWidth() / 2.0f,
                        entity->getY() - entity->getHeight() / 2.0f,
                        entity->getWidth(), entity->getHeight()};
      Vector2 origin = {0, 0};
      DrawTexturePro(bossTexture, source, dest, origin, 0.0f, WHITE);
    }
  }
}

void GameView::drawBossHealthBar(const Boss &boss) {
  float barWidth = 300;
  float barHeight = 20;
  float x = (GetScreenWidth() - barWidth) / 2;
  float y = 20;

  float healthRatio = (float)boss.getHealth() / boss.getMaxHealth();
  float healthWidth = barWidth * healthRatio;

  DrawRectangle(x, y, barWidth, barHeight, DARKGRAY);

  DrawRectangle(x, y, healthWidth, barHeight, RED);

  DrawRectangleLines(x, y, barWidth, barHeight, WHITE);
}

void GameView::drawCollider(
    const std::vector<std::shared_ptr<Entity>> &entities) {

  for (auto &entity : entities) {
    DrawRectangleLines(entity->getX() - entity->getWidth() / 2.0f,
                       entity->getY() - entity->getHeight() / 2.0f,
                       entity->getWidth(), entity->getHeight(), RED);
  }
}
