#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Entity/Asteroid/Asteroid.h"
#include "../Entity/Entity.h"
#include "../Entity/Player/Player.h"
#include "../GameView/GameView.h"
#include <algorithm>
#include <memory>
#include <raylib.h>
#include <vector>

class GameController {
private:
  const std::shared_ptr<GameView> &view;
  GameState state = GameState::MENU;
  bool bossHasSpawned = false;
  float bossSpawnTime = 0.0f;
  bool bossAppearing = false;
  std::vector<std::shared_ptr<Bullet>> bullets;
  std::vector<std::shared_ptr<Asteroid>> &asteroids;
  std::shared_ptr<Player> &player;
  std::shared_ptr<Boss> boss;

  void fallBlocksUpdate();
  void updatePlayer();

  void spawnBoss();
  Music spaceMusic;
  Music bossMusic;
  Sound shotSound;
  Sound bossIntroSound;

  void shutdown();

  void updateBullets();

  void updateBoss();

public:
  GameController(const std::shared_ptr<GameView> &view,
                 std::shared_ptr<Player> &player,
                 std::vector<std::shared_ptr<Asteroid>> &asteroids);
  void update();
  void manageColission();
  GameState getState() const;
  void setState(GameState state);
  bool gameExit() const;
};

template <typename T>
void entityCleaner(std::vector<std::shared_ptr<T>> &entities) {
  entities.erase(
      std::remove_if(entities.begin(), entities.end(),
                     [](const std::shared_ptr<T> &e) { return !e->isAlive(); }),
      entities.end());
}

template <typename T>
void pushEntities(std::vector<std::shared_ptr<T>> &entities,
                  std::vector<std::shared_ptr<Entity>> &e) {

  for (auto &entity : entities) {
    e.push_back(entity);
  }
}

#endif
