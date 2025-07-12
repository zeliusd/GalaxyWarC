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
  if (!this->bossHasSpawned) {
    spawnBoss();
  } else {
    if (this->boss->isAlive()) {
      updateBoss();
    }
  }

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
    float y = bullet->getY();
    float halfH = bullet->getHeight() / 2.0f;

    if (y + halfH < 0 || y - halfH > GetScreenHeight()) {
      bullet->onCollision(*bullet);
    }
    bullet->move(GetFrameTime(), 0);
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
  if (!this->asteroids.empty())
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

void GameController::updateBoss() {
  if (!this->bossHasSpawned || !this->boss)
    return;

  float speed = this->boss->getSpeed();
  float newX = this->boss->getX() + speed * GetFrameTime();

  if (newX - this->boss->getWidth() / 2 < 0 ||
      newX + this->boss->getWidth() / 2 > GetScreenWidth()) {
    speed *= -1;
    this->boss->setSpeed(speed);

    newX = this->boss->getX() + speed * GetFrameTime();
  }

  this->boss->move(newX - this->boss->getX(), 0);

  static float lastShot = 0.0f;
  float now = GetTime();

  if (now - lastShot > 1.5f) { // Dispara cada 1.5 segundos
    auto bossBullets = boss->shotBullets();
    for (auto &bullet : bossBullets) {
      bullets.push_back(bullet);
      view->addView(std::make_shared<BulletView>(bullet));
    }
    lastShot = now;
  }
}
