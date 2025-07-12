#include "GameController.h"
#include "../Entity/Blocks/Bloque.h"
#include "Entity/Boss/Boss.h"
#include "Entity/Entity.h"
#include "GameView/View/BossView/BossView.h"
#include "GameView/View/BulletView/BulletView.h"
#include "raylib.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

extern unsigned char spaceship_wav[];
extern unsigned int spaceship_wav_len;

extern unsigned char Fire1_wav[];
extern unsigned int Fire1_wav_len;

extern unsigned char bosstrack_mp3[];
extern unsigned int bosstrack_mp3_len;

GameController::GameController(const std::shared_ptr<GameView> &view,
                               std::shared_ptr<Player> &player,
                               std::vector<std::shared_ptr<Bloque>> &asteroids)
    : view(view), player(player), asteroids(asteroids) {
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

void GameController::update() {
  UpdateMusicStream(actualMusic);

  updatePlayer();
  spawnBoss();
  fallBlocksUpdate();
  manageColission();
  updateBullets();
  entityCleaner(this->bullets);
  entityCleaner(this->asteroids);

  view->draw();
}

void GameController::updatePlayer() {

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
    auto bullet = player->shotBullet();
    this->bullets.push_back(bullet);
    this->view->addView(std::make_shared<BulletView>(bullet));
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

void GameController::fallBlocksUpdate() {
  for (auto &entity : this->asteroids) {
    entity->move(entity->getX(), 100 * GetFrameTime());
    if (entity->getY() - entity->getHeight() / 2 > GetScreenHeight()) {
      entity->onCollision(*entity);
    }
  }
}

void GameController::updateBullets() {
  for (auto &bullet : this->bullets) {
    bullet->move(bullet->getX(), -450 * GetFrameTime());
    if (bullet->getY() + bullet->getHeight() / 2 < 0) {
      bullet->onCollision(*bullet);
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

void GameController::manageColission() {
  std::vector<std::shared_ptr<Entity>> entities;
  pushEntities(this->bullets, entities);
  pushEntities(this->asteroids, entities);
  entities.push_back(this->player);
  if (this->boss != nullptr && this->boss->isAlive()) {
    entities.push_back(this->boss);
  }
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
void GameController::spawnBoss() {
  if (bossHasSpawned || !this->asteroids.empty())
    return;

  float centerX = GetScreenWidth() / 2.0f;
  auto boss = std::make_shared<Boss>(centerX, 140);
  this->boss = boss;
  this->view->addView(std::make_shared<BossView>(boss));
  this->bossHasSpawned = true;
  StopMusicStream(actualMusic);
  UnloadMusicStream(actualMusic);

  actualMusic =
      LoadMusicStreamFromMemory(".mp3", bosstrack_mp3, bosstrack_mp3_len);
  PlayMusicStream(actualMusic);
}
