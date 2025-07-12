// GameView.h
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View/View.h"
#include "raylib.h"
#include <memory>
#include <vector>

class GameView {

private:
  Texture2D backgroundTexture;
  std::vector<std::shared_ptr<View>> &entities;

  void drawEntities();
  bool debug = false;
  void drawCollider();
  void drawBackground();

public:
  GameView(std::vector<std::shared_ptr<View>> &entities);
  ~GameView();
  void draw();
  void addView(std::shared_ptr<View> view);
};

#endif
