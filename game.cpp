#include "game.h"
#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Movement timing
unsigned long lastRotateTime;
unsigned long rotateDelay = 150;
unsigned long lastMoveTime;
unsigned long moveDelay = 100;

// Gravity timing
unsigned long lastFallTime;
const unsigned long REGULAR_FALL_DELAY = 400;
const unsigned long FAST_FALL_DELAY = 50;
unsigned long fallDelay = REGULAR_FALL_DELAY;

/*
  The constructor for the game object
  Called whenever we create a new game
  Takes a pointer to an instance of a renderer to be used to do any drawing
*/
Game::Game ( Renderer *renderer, Connection *connection ) : renderer_(renderer), connection_(connection) {

  // Make sure we set the game to not over
  gameOver_ = false;

  // Set the initial score
  score_ = 0;

  // Create a new stage for the game
  stage_ = new Stage();

  // Seed the random number generator and generate first block
  int shape = random( 0, 7 );

  // Create a new block for the game
  block_ = new Block( 5, 0, colors[shape], shape );

  // Generate shape of second block
  shape = random( 0, 7 );

  // Create the next block
  nextBlock_ = new Block( 5, 0, colors[shape], shape );
  
  // Register block with stage
  stage_->block( block_ );

  // Do initial render of stage
  renderer_->initialRender( stage_ );

  // Draw the next block
  drawNextBlock();

  // Draw the score
  drawScore();

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
    fallDelay = FAST_FALL_DELAY;

  }
  else {
    fallDelay = REGULAR_FALL_DELAY;
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
    stage_->pushRows(1);
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
      int rowsCleared = stage_->placeBlock( block_ );

      // Dealloc old block
      delete block_;

      // Create new block
      block_ = nextBlock_; //new Block( 5, 0, colors[nextBlock_], nextBlock_ );

      // Assign the next block a random type
      int shape = random( 0, 7 );

      nextBlock_ = new Block( 5, 0, colors[shape], shape );

      // Register new block with stage
      stage_->block( block_ );

      // Check if the block immediately collides, if it does, then the player loses
      if( stage_->collides( block_ ) ) {
	gameOver_ = true;
      }

      // Draw the next block to be spawned
      drawNextBlock();

      // Update the score
      updateScore( rowsCleared );

      // Update the score display
      drawScore();

    }

    // Update the last fall time
    lastFallTime = updateTime;
  }

  // Check for serial data to push rows
  int rData = connection_->read();
  
  // If we received a positive integer, push that many rows
  if( rData > 0 ) {
    stage_->pushRows( rData );
  }
  else if( rData == -1 ) {
    // End game
    gameOver_ = true;
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

/*
  Draws the next block to be spawned
 */
void Game::drawNextBlock() {

  int left_bound = 7 + stage_->width() * stage_->blockWidth();
  int top_bound = 30;

  // Erase
  renderer_->fillRect( left_bound, top_bound, 128 - left_bound, 4 * stage_->blockHeight(), 0x0000 );

  // Draw the text
  renderer_->drawText( left_bound - 2, top_bound - 11, "Next:" );

  // Display the next block to be created
  for( int x = -2; x < 2; x++ ) {
    for( int y = -1; y < 3; y++ ) {
      if( nextBlock_->intersects( nextBlock_->x() + x, nextBlock_->y() + y ) ) {
	renderer_->fillRect( left_bound + (x+2) * stage_->blockWidth(), top_bound + y * stage_->blockHeight(), stage_->blockWidth() - 1, stage_->blockHeight() - 1, colors[nextBlock_->shape()] );
      }
    }
  }
}

/*
  Draws the player's score
 */
void Game::drawScore() {
  
  int left_bound = 7 + stage_->width() * stage_->blockWidth();
  int top_bound = 50;

  // Erase
  renderer_->fillRect( left_bound, top_bound, 128 - left_bound, 20, 0x0000 );

  // Write the integer score to a charbuffer
  char buf[8];
  sprintf( buf, "%d", score_ );

  // Draw text
  renderer_->drawText( left_bound - 2, top_bound, "Score:" );
  renderer_->drawText( left_bound, top_bound + 10, buf );

}

/*
  Update the player's score based on the number of rows cleared and combo multiplier
*/
void Game::updateScore( int rowsCleared ) {

  // Increase the combo multiplier
  combo_++;

  switch( rowsCleared ) {

  // Single
  case 1:
    score_ += 100 + 100 * combo_;
    break;
  
  // Double
  case 2:
    score_ += 300 + 100 * combo_;
    break;
  
  // Triple
  case 3:
    score_ += 500 + 100 * combo_;
    break;
  
  // Tetris
  case 4:
    score_ += 800 + 100 * combo_;
    break;

  // No clear
  default:
    // Reset their combo multiplier
    combo_ = 0;
    break;

  }

  // Send lines equal to the combo multiplier
  if( combo_ > 0 ) {
    connection_->write( combo_ );
  }

  // Draw the new combo multiplier
  int left_bound = 7 + stage_->width() * stage_->blockWidth();
  int top_bound = 70;

  // Erase
  renderer_->fillRect( left_bound, top_bound, 128 - left_bound, 20, 0x0000 );

  // Write the integer combo to a charbuffer
  char buf[8];
  sprintf( buf, "%dx", combo_ );

  // Draw text
  renderer_->drawText( left_bound - 2, top_bound, "Combo:" );
  renderer_->drawText( left_bound, top_bound + 10, buf );
}
