/*
  Game Controller
  ---------------------------------
  Handles all game logic, including
  updates, physics, gamestate, etc
 */
#ifndef GAME_H
#define GAME_H

#include "input.h"

class Game {
  
public:
  
  // Constructor
  Game();

  // Applies input to the game stage each frame
  void handleInput( InputHandler *ih );

  // Updates the game state each frame
  void update();

  // Draws the game state to the screen
  void draw();

private:

  int speed_; // The speed multiplier that the game will run at. Default 1

};

#endif
