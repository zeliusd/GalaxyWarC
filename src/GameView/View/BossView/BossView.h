#ifndef BOSSVIEW_H
#define BOSSVIEW_H

#include "../../../Entity/Boss/Boss.h"
#include "../View.h"
#include "raylib.h"
#include <memory>

extern unsigned char boss_png[];
extern unsigned int boss_png_len;

class BossView : public View {
private:
  Texture2D bossTexture;
  std::shared_ptr<Boss> boss;

  void drawBossBar();

public:
  BossView(std::shared_ptr<Boss> boss);
  void draw() override;
  void unloadTexture() override;
  std::shared_ptr<Entity> getReference() override;
  bool isAlive() override;
};

#endif
