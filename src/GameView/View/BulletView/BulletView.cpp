#include "BulletView.h"

BulletView::BulletView(std::shared_ptr<Bullet> &bullet) {
  this->bullet = bullet;
  Image bulletImage = LoadImageFromMemory(".png", bullet_png, bullet_png_len);
  this->bulletTexture = LoadTextureFromImage(bulletImage);
  UnloadImage(bulletImage);
}

void BulletView::draw() {
  if (!this->bullet->isAlive()) {
    return;
  }

  Rectangle source = {0, 0, (float)bulletTexture.width,
                      (float)bulletTexture.height};
  Rectangle dest = {bullet->getX(), bullet->getY(), bullet->getWidth(),
                    bullet->getHeight()};

  Vector2 origin = {dest.width / 2.0f, dest.height / 2.0f};

  float rotation = bullet->isPlayerBullet() ? 0.0f : 180.0f;

  DrawTexturePro(bulletTexture, source, dest, origin, rotation, WHITE);
}

std::shared_ptr<Entity> BulletView::getReference() { return this->bullet; }

bool BulletView::isAlive() { return this->bullet->isAlive(); }

void BulletView::unloadTexture() { UnloadTexture(this->bulletTexture); }
