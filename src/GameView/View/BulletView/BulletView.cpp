
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
  Rectangle dest = {this->bullet->getX() - this->bullet->getWidth() / 2.0f,
                    this->bullet->getY() - this->bullet->getHeight() / 2.0f,
                    this->bullet->getWidth(), this->bullet->getHeight()};
  Vector2 origin = {0, 0};
  DrawTexturePro(bulletTexture, source, dest, origin, 0.0f, WHITE);
}

std::shared_ptr<Entity> BulletView::getReference() { return this->bullet; }

bool BulletView::isAlive() { return this->bullet->isAlive(); }

void BulletView::unloadTexture() { UnloadTexture(this->bulletTexture); }
