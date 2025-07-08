#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Entity/Entity.h"
#include "../Player/Player.h"
#include <memory>
#include <vector>
class GameController {
private:
  void fallBlocksUpdate(std::vector<std::shared_ptr<Entity>> &entities);
  void updatePlayer(std::vector<std::shared_ptr<Entity>> &entities,
                    std::shared_ptr<Player> &player);

public:
  void update(std::vector<std::shared_ptr<Entity>> &entities,
              std::shared_ptr<Player> &player);
  void manageColission(std::vector<std::shared_ptr<Entity>> &entities);
};

#endif
