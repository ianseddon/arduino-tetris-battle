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
#include "connection.h"

class Game {
  
public:
  
  // Constructor
  Game( Renderer *renderer, Connection *connection );
  // Destructor
  ~Game();

  // Applies input to the game stage each frame
  void handleInput( InputHandler *ih );

  // Updates the game state each frame
  void update( unsigned long dt );

  // Draws the game state to the screen
  void draw();

  // Draws the next block to be spawned to the sidebar
  void drawNextBlock();

  // Draws the player's score
  void drawScore();

  // Update the score
  void updateScore( int rowsCleared );

  // Return whether the game is over
  bool gameOver() const { return gameOver_; }

  // Getters for objects
  Stage* stage() const { return stage_; }
  Block* block() const { return block_; }

  bool won() const { return won_; }

private:

  Renderer *renderer_; // The pointer to the renderer instance
  Connection *connection_; // The pointer to the connection instance
  Stage *stage_;       // The pointer to the stage instance
  Block *block_;       // The pointer to the block instance
  Block *nextBlock_;   // The pointer to the next block instance

  int speed_;          // The speed multiplier that the game will run at. Default 1
  bool gameOver_;      // Is the game over?
  bool won_;           // Did we win?

  int score_;          // The player's score
  int combo_;          // The player's combo multiplier

};

#endif
