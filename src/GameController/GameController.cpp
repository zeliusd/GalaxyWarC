#include "GameController.h"
#include "../Entity/Boss/Boss.h"
#include "../Entity/Bullet/Bullet.h"
#include "../resources/tracks/Fire1.c"
#include "../resources/tracks/bosstrack.c"
#include "../resources/tracks/spaceship.c"
#include "Blocks/Bloque.h"
#include "Entity/Entity.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>

GameController::GameController() {
  this->actualMusic =
      LoadMusicStreamFromMemory(".wav", spaceship_wav, spaceship_wav_len);
  PlayMusicStream(this->actualMusic);

  Wave fireWave = LoadWaveFromMemory(".wav", Fire1_wav, Fire1_wav_len);
  shotSound = LoadSoundFromWave(fireWave);
  UnloadWave(fireWave);
}

void GameController::shutdown() {
  StopMusicStream(actualMusic);
  UnloadMusicStream(actualMusic);
  UnloadSound(shotSound);
}
void GameController::update(std::vector<std::shared_ptr<Entity>> &entities,
                            std::shared_ptr<Player> &player) {
  UpdateMusicStream(actualMusic);

  updatePlayer(entities, player);
  spawnBoss(entities);
  fallBlocksUpdate(entities);
  manageColission(entities);

  entities.erase(std::remove_if(entities.begin(), entities.end(),
                                [](const std::shared_ptr<Entity> &e) {
                                  return !e->isAlive();
                                }),
                 entities.end());
}

void GameController::updatePlayer(
    std::vector<std::shared_ptr<Entity>> &entities,
    std::shared_ptr<Player> &player) {

  const float velocidad = player->getSpeed() * GetFrameTime();

  float dx = 0, dy = 0;
  if (IsKeyDown(KEY_D))
    dx += velocidad;
  if (IsKeyDown(KEY_A))
    dx -= velocidad;
  if (IsKeyDown(KEY_S))
    dy += velocidad;
  if (IsKeyDown(KEY_W))
    dy -= velocidad;

  static double tiempoUltimoDisparo = 0;
  double tiempoActual = GetTime();  // en segundos
  double tiempoEntreDisparos = 0.3; // medio segundo entre disparos

  if (IsKeyDown(KEY_SPACE) &&
      (tiempoActual - tiempoUltimoDisparo) > tiempoEntreDisparos) {
    entities.push_back(player->shotBullet());
    PlaySound(shotSound);
    tiempoUltimoDisparo = tiempoActual;
  }

  player->move(dx, dy);

  float x = player->getX();
  float y = player->getY();
  float w = player->getWidth();
  float h = player->getHeight();
  if (x < w / 2.0f)
    x = w / 2.0f;
  if (x > GetScreenWidth() - w / 2.0f)
    x = GetScreenWidth() - w / 2.0f;
  if (y < h / 2.0f)
    y = h / 2.0f;
  if (y > GetScreenHeight() - h / 2.0f)
    y = GetScreenHeight() - h / 2.0f;

  player->move(x - player->getX(), y - player->getY());
}

void GameController::fallBlocksUpdate(
    std::vector<std::shared_ptr<Entity>> &entities) {
  for (auto &entity : entities) {
    if (dynamic_cast<Bloque *>(entity.get()) != nullptr) {
      entity->move(entity->getX(), 100 * GetFrameTime());
      if (entity->getY() - entity->getHeight() / 2 > GetScreenHeight()) {
        entity->onCollision(*entity);
      }
    }
    if (dynamic_cast<Bullet *>(entity.get()) != nullptr) {
      entity->move(entity->getX(), -450 * GetFrameTime());
      if (entity->getY() + entity->getHeight() / 2 < 0) {
        entity->onCollision(*entity);
      }
    }
  }
}

Rectangle getEntityRectangle(const Entity &e) {
  return {e.getX() - e.getWidth() / 2.0f, e.getY() - e.getHeight() / 2.0f,
          e.getWidth(), e.getHeight()};
}

bool checkCollisionEntidad(const Entity &a, const Entity &b) {
  Rectangle r1 = getEntityRectangle(a);
  Rectangle r2 = getEntityRectangle(b);

  return CheckCollisionRecs(r1, r2);
}

void GameController::manageColission(
    std::vector<std::shared_ptr<Entity>> &entities) {
  for (size_t i = 0; i < entities.size(); ++i) {
    for (size_t j = i + 1; j < entities.size(); ++j) {
      auto &a = entities[i];
      auto &b = entities[j];

      if (checkCollisionEntidad(*a, *b)) {
        std::cout << "Colisión entre: " << a->getX() << "," << a->getY()
                  << " y " << b->getX() << "," << b->getY() << std::endl;

        a->onCollision(*b);
        b->onCollision(*a);
      }
    }
  }
}

void GameController::spawnBoss(std::vector<std::shared_ptr<Entity>> &entities) {
  if (bossHasSpawned)
    return;
  for (auto &entity : entities) {
    if (dynamic_cast<Bloque *>(entity.get()) != nullptr ||
        dynamic_cast<Boss *>(entity.get())) {
      return;
    }
  }
  float centerX = GetScreenWidth() / 2.0f;
  entities.push_back(std::make_shared<Boss>(centerX, 140));
  this->bossHasSpawned = true;
  StopMusicStream(actualMusic);
  UnloadMusicStream(actualMusic);

  actualMusic =
      LoadMusicStreamFromMemory(".mp3", bosstrack_mp3, bosstrack_mp3_len);
  PlayMusicStream(actualMusic);
}
