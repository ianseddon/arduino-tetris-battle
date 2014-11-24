#include "game.h"

/*
  The constructor for the game object
  Called whenever we create a new game
*/
Game::Game () {

  // Create a new stage for the game
  stage_ = new Stage();

}

/*
  The destructor for the game object.
  We need to make sure we free the memory used
  by the stage object and anything else we've allocated
 */
Game::~Game () {

  // Dealloc the stage
  delete stage_;

}

void Game::handleInput( InputHandler *ih ) {
  
}

void Game::update() {

}

void Game::draw() {

}
