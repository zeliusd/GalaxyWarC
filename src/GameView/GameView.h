// GameView.h
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../Entity/Entity.h"
#include <memory>
#include <vector>
class GameView {

public:
  void draw(const std::vector<std::shared_ptr<Entity>> &entities);
};

#endif
