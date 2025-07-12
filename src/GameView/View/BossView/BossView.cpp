
#include "BossView.h"
#include "Entity/Boss/Boss.h"

BossView::BossView(std::shared_ptr<Boss> boss) {

  this->boss = boss;
  Image bossImage = LoadImageFromMemory(".png", boss_png, boss_png_len);

  this->bossTexture = LoadTextureFromImage(bossImage);
  UnloadImage(bossImage);
}

void BossView::draw() {
  if (!this->boss->isAlive()) {
    return;
  }
  Rectangle source = {0, 0, (float)bossTexture.width,
                      (float)bossTexture.height};
  Rectangle dest = {this->boss->getX() - this->boss->getWidth() / 2.0f,
                    this->boss->getY() - this->boss->getHeight() / 2.0f,
                    this->boss->getWidth(), this->boss->getHeight()};
  Vector2 origin = {0, 0};
  DrawTexturePro(bossTexture, source, dest, origin, 0.0f, WHITE);

  this->drawBossBar();
}

void BossView::drawBossBar() {
  float barWidth = 300;
  float barHeight = 20;
  float x = (GetScreenWidth() - barWidth) / 2;
  float y = 20;

  float healthRatio =
      (float)this->boss->getHealth() / this->boss->getMaxHealth();
  float healthWidth = barWidth * healthRatio;

  DrawRectangle(x, y, barWidth, barHeight, DARKGRAY);

  DrawRectangle(x, y, healthWidth, barHeight, RED);

  DrawRectangleLines(x, y, barWidth, barHeight, WHITE);
}

std::shared_ptr<Entity> BossView::getReference() { return this->boss; }

bool BossView::isAlive() { return this->boss->isAlive(); }

void BossView::unloadTexture() { UnloadTexture(this->bossTexture); }
