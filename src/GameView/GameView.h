// GameView.h
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../Entity/Entity.h"
#include "../Player/Player.h"
#include "raylib.h"
#include <memory>
#include <vector>

class GameView {

private:
  Texture2D playerTexture;
  Texture2D asteroidTexture;
  Texture2D backgroundTexture;
  Texture2D bossTexture;
  Texture2D bulletTexture;

  void drawPlayer(const std::shared_ptr<Player> &player);
  void drawEntities(const std::vector<std::shared_ptr<Entity>> &entities);
  void drawBossHealthBar(const Boss &boss);
  bool debug = false;
  void drawCollider(const std::vector<std::shared_ptr<Entity>> &entities);

public:
  GameView();
  ~GameView();
  void draw(const std::vector<std::shared_ptr<Entity>> &entities,
            const std::shared_ptr<Player> &player);
};

#endif
