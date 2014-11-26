/*
  Game Controller
  ---------------------------------
  Handles all game logic, including
  updates, physics, gamestate, etc
 */
#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "stage.h"
#include "block.h"
#include "renderer.h"

class Game {
  
public:
  
  // Constructor
  Game( Renderer *renderer );
  // Destructor
  ~Game();

  // Applies input to the game stage each frame
  void handleInput( InputHandler *ih );

  // Updates the game state each frame
  void update( unsigned long dt );

  // Draws the game state to the screen
  void draw();

  // Return whether the game is over
  bool gameOver() const { return gameOver_; }

private:

  Renderer *renderer_; // The pointer to the renderer instance
  Stage *stage_;       // The pointer to the stage instance
  Block *block_;       // The pointer to the block instance

  int speed_;          // The speed multiplier that the game will run at. Default 1
  bool gameOver_;      // Is the game over?

};

#endif
