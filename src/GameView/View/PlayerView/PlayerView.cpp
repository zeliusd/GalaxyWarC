#include "PlayerView.h"

PlayerView::PlayerView(std::shared_ptr<Player> player) {
  this->player = player;
  Image naveImage = LoadImageFromMemory(".png", nave_png, nave_png_len);
  this->playerTexture = LoadTextureFromImage(naveImage);
  UnloadImage(naveImage);
}

void PlayerView::draw() {
  if (!this->player->isAlive()) {
    return;
  }
  Rectangle source = {0, 0, (float)playerTexture.width,
                      (float)playerTexture.height};
  Rectangle dest = {player->getX() - player->getWidth() / 2.0f,
                    player->getY() - player->getHeight() / 2.0f,
                    player->getWidth(), player->getHeight()};
  Vector2 origin = {0, 0};
  DrawTexturePro(playerTexture, source, dest, origin, 0.0f, WHITE);
}

std::shared_ptr<Entity> PlayerView::getReference() { return this->player; }

bool PlayerView::isAlive() { return this->player->isAlive(); }

void PlayerView::unloadTexture() { UnloadTexture(this->playerTexture); }
