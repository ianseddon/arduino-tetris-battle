#include "game.h"
#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Movement timing
unsigned long lastRotateTime;
unsigned long rotateDelay = 200;

unsigned long lastMoveTime;
unsigned long moveDelay = 50;

unsigned long lastFallTime;
unsigned long fallDelay = 300;

unsigned long lastFpsDrawTime;
unsigned long fpsDrawDelay = 100;

/*
  The constructor for the game object
  Called whenever we create a new game
*/
Game::Game () {

  // Initialize the display
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

  unsigned long inputTime = millis();

  // Handle joystick down
  if( ih->down() ) {

    // Speed up the block falling

  }

  // Handle joystick up
  if( ih->up() ) {
    
    // Rotate the block if we've passed the delay
    if( inputTime > lastRotateTime + rotateDelay ) {
      // Rotate the block
      block_->rotate();

      // Check for collision
      if( stage_->collides( block_ ) ) {
	// Collided so stop
	block_->unrotate();
      }
      // No collision, so update the last rotate time
      else {
	// Update the last rotation time
	lastRotateTime = inputTime;
      }

    }

  }

  // Handle joystick left
  if( ih->left() ) {

    // Move the block left if we've passed the delay
    if( inputTime > lastMoveTime + moveDelay ) {
      
      // Move the block
      block_->x( block_->x() - 1 );

      // Check for collision
      if( stage_->collides( block_ ) ) {
	// Collided, so stop
	block_->x( block_->x() + 1 );
      }
      // No collision, so update the last move time
      else {
	// Update the last movement time
	lastMoveTime = inputTime;
      }

    }

  }

  // Handle joystick right
  if( ih->right() ) {

    // Move the block if we've passed the delay
    if( inputTime > lastMoveTime + moveDelay ) {

      // Move the block
      block_->x( block_->x() + 1 );

      // Check for collision
      if( stage_->collides( block_ ) ) {
	// Collided, so stop
	block_->x( block_->x() - 1 );
      }
      // No collision, so update the last move time
      else {
	// Update the last movement time
	lastMoveTime = inputTime;
      }

    }

  }

  // Handle joystick select
  if( ih->select() ) {

  }

}

/*
  The step of each frame in which the game logic is applied
  before rendering that frame
 */
void Game::update( unsigned long dt ) {

  unsigned long updateTime = millis();

  // Make the block fall if we've passed the delay
  if( updateTime > lastFallTime + fallDelay ) {

    // Move the block
    block_->y( block_->y() + 1 );

    // Check for collision
    if( stage_->collides( block_ ) ) {
      // Collided, so stop
      block_->y( block_->y() - 1 );

      // Place the block

    }

    // Update the last fall time
    lastFallTime = updateTime;
  }

  // Draw the FPS
  if( updateTime > lastFpsDrawTime + fpsDrawDelay ) {
    char fBuf[15];
    sprintf( fBuf, "%d", (int) ( 1000 / dt ) );
    renderer_->fillRect( stage_->width() * stage_->blockWidth() + 5, 0, 20, 15, 0x000000 );
    renderer_->drawText( stage_->width() * stage_->blockWidth() + 5, 3, fBuf );
    renderer_->drawText( "fps" );
    lastFpsDrawTime = updateTime;
  }

}

/*
  Render the current frame after all game logic for that frame
  has been applied
 */
void Game::draw() {
  
  // send the stage to the renderer to be displayed to screen
  renderer_->render( stage_ );

}
