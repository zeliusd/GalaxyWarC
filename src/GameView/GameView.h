// GameView.h
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../Player/Player.h"
#include "raylib.h"

class GameView {

public:
  void draw(const Player &player);
};

#endif
