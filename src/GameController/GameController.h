#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Entity/Entity.h"
#include "../Player/Player.h"
#include <memory>
#include <vector>
class GameController {
private:
  bool bossHasSpawned = false;
  void fallBlocksUpdate(std::vector<std::shared_ptr<Entity>> &entities);
  void updatePlayer(std::vector<std::shared_ptr<Entity>> &entities,
                    std::shared_ptr<Player> &player);
  void spawnBoss(std::vector<std::shared_ptr<Entity>> &entities);

public:
  void update(std::vector<std::shared_ptr<Entity>> &entities,
              std::shared_ptr<Player> &player);
  void manageColission(std::vector<std::shared_ptr<Entity>> &entities);
};

#endif
