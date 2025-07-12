
#include "AsteroidView.h"

AsteroidView::AsteroidView(std::shared_ptr<Bloque> asteroid) {
  this->asteroid = asteroid;
  Image asteroidImage =
      LoadImageFromMemory(".png", asteroid_png, asteroid_png_len);

  asteroidTexture = LoadTextureFromImage(asteroidImage);
  UnloadImage(asteroidImage);
}

void AsteroidView::draw() {
  if (!this->asteroid->isAlive()) {
    return;
  }
  Rectangle source = {0, 0, (float)asteroidTexture.width,
                      (float)asteroidTexture.height};
  Rectangle dest = {this->asteroid->getX() - this->asteroid->getWidth() / 2.0f,
                    this->asteroid->getY() - this->asteroid->getHeight() / 2.0f,
                    this->asteroid->getWidth(), this->asteroid->getHeight()};
  Vector2 origin = {0, 0};
  DrawTexturePro(asteroidTexture, source, dest, origin, 0.0f, WHITE);
}

std::shared_ptr<Entity> AsteroidView::getReference() { return this->asteroid; }

bool AsteroidView::isAlive() { return this->asteroid->isAlive(); }

void AsteroidView::unloadTexture() { UnloadTexture(this->asteroidTexture); }
