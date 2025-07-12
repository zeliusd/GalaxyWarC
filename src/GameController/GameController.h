#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Entity/Entity.h"
#include "../Entity/Player/Player.h"
#include "../GameView/GameView.h"
#include <memory>
#include <raylib.h>
#include <vector>
class GameController {
private:
  const std::shared_ptr<GameView> &view;
  bool bossHasSpawned = false;
  void fallBlocksUpdate(std::vector<std::shared_ptr<Entity>> &entities);
  void updatePlayer(std::vector<std::shared_ptr<Entity>> &entities,
                    std::shared_ptr<Player> &player);
  void spawnBoss(std::vector<std::shared_ptr<Entity>> &entities);
  Music actualMusic;
  Sound shotSound;
  void shutdown();

public:
  GameController(const std::shared_ptr<GameView> &view);
  void update(std::vector<std::shared_ptr<Entity>> &entities,
              std::shared_ptr<Player> &player);
  void manageColission(std::vector<std::shared_ptr<Entity>> &entities);
};

#endif
