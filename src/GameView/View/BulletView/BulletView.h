#ifndef BULLETVIEW_H
#define BULLETVIEW_H

#include "../../../Entity/Bullet/Bullet.h"
#include "../View.h"
#include "raylib.h"
#include <memory>

extern unsigned char bullet_png[];
extern unsigned int bullet_png_len;

class BulletView : public View {
private:
  Texture2D bulletTexture;
  std::shared_ptr<Bullet> bullet;

public:
  BulletView(std::shared_ptr<Bullet> &bullet);
  void draw() override;
  void unloadTexture() override;
  std::shared_ptr<Entity> getReference() override;
};

#endif
