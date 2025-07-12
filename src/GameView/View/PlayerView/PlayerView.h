
#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "../../../Entity/Player/Player.h"
#include "../View.h"
#include "Entity/Entity.h"
#include "raylib.h"
#include <memory>

extern unsigned char nave_png[];
extern unsigned int nave_png_len;

class PlayerView : public View {
private:
  Texture2D playerTexture;
  std::shared_ptr<Player> player;

public:
  PlayerView(std::shared_ptr<Player> player);
  void draw() override;
  void unloadTexture() override;
  std::shared_ptr<Entity> getReference() override;
  bool isAlive() override;
};

#endif
