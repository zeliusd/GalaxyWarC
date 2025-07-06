#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Entity/Entity.h"
#include <memory>
#include <vector>
class GameController {
public:
  void update(std::vector<std::shared_ptr<Entity>> &entities);
  void manageColission(std::vector<std::shared_ptr<Entity>> &entities);
};

#endif
