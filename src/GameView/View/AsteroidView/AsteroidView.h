
#ifndef ASTEROIDVIEW_H
#define ASTEROIDVIEW_H

#include "../../../Blocks/Bloque.h"
#include "../View.h"
#include "raylib.h"
#include <memory>

extern unsigned char asteroid_png[];
extern unsigned int asteroid_png_len;

class AsteroidView : public View {
private:
  Texture2D asteroidTexture;
  std::shared_ptr<Bloque> asteroid;

public:
  AsteroidView(std::shared_ptr<Bloque> asteroid);
  void draw() override;
  void unloadTexture() override;
  std::shared_ptr<Entity> getReference() override;
  bool isAlive() override;
};

#endif
