#include "game.h"
#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/*
  The constructor for the game object
  Called whenever we create a new game
*/
Game::Game () {

  Adafruit_ST7735 tft = Adafruit_ST7735( TFT_CS, TFT_DC, TFT_RST );

  // Create a new renderer for the game
  renderer_ = new Renderer( tft );

  // Create a new stage for the game
  stage_ = new Stage();

  int shape = 5;// random( 0, 7 );

  // Create a new block for the game
  block_ = new Block( 5, 0, colors[shape], shape );

  // Register block with stage
  stage_->block( block_ );

  // Do initial render of stage
  renderer_->initialRender( stage_ );

}

/*
  The destructor for the game object.
  We need to make sure we free the memory used
  by the stage object and anything else we've allocated
 */
Game::~Game () {

  // Dealloc the block
  delete block_;

  // Dealloc the stage
  delete stage_;

  // Dealloc the renderer
  delete renderer_;

}

/*
  The step each frame in which we handle any input from the user
  and apply it to the game state
 */
void Game::handleInput( InputHandler *ih ) {

  // Handle joystick down
  if( ih->down() ) {
    block_->y( block_->y() + 1 );
  }

  // Handle joystick up
  if( ih->up() ) {
    block_->y( block_->y() - 1 );
  }

  // Handle joystick left
  if( ih->left() ) {
    
  }

  // Handle joystick right
  if( ih->right() ) {
    
  }

  // Handle joystick select
  if( ih->select() ) {
    block_->rotate();
  }

}

/*
  The step of each frame in which the game logic is applied
  before rendering that frame
 */
void Game::update( unsigned long dt ) {

}

/*
  Render the current frame after all game logic for that frame
  has been applied
 */
void Game::draw() {
  
  // send the stage to the renderer to be displayed to screen
  renderer_->render( stage_ );

}
