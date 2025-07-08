// GameView.h
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../Entity/Entity.h"
#include "../Player/Player.h"
#include <memory>
#include <vector>

class GameView {

private:
  void drawPlayer(const std::shared_ptr<Player> &player);
  void drawEntities(const std::vector<std::shared_ptr<Entity>> &entities);

public:
  void draw(const std::vector<std::shared_ptr<Entity>> &entities,
            const std::shared_ptr<Player> &player);
};

#endif
