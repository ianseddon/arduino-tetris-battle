#include "stage.h"

const unsigned long BG_COLOR = 0x000000;

Stage::Stage() {

  // Set the memory for the placed blocks
  memset( placedBlocks_, BG_COLOR, sizeof( placedBlocks_ ) );

  // Set the memory for the buffers
  memset( buffer_, BG_COLOR, sizeof( buffer_ ) );
  memset( buffer_last_, BG_COLOR, sizeof( buffer_last_ ) );

}

bool Stage::shouldDraw( int x, int y ) {

  return ( buffer_[y][x] != buffer_last_[y][x] );

}

/*
  Composes a buffer from the data of the background layer, placed block data and controlled block
  into the data that will be displayed this frame
 */
void Stage::composeBuffer() {
  
  // Iterate through stage, compositing background layer, placed blocks and controlled block into a single buffer
  for( int y = 0; y < this->height(); y++ ) {
    for( int x = 0; x < this->width(); x++ ) {
  
      // Check if the block pointer is assigned
      if( block_ && block_->intersects( x, y ) ) {
	// If the block exists in this position, set the buffer to the block's color
	buffer_[y][x] = block_->color();
      }
      // Otherwise set the buffer to the color in the placed blocks arr
      else {
	buffer_[y][x] = placedBlocks_[y][x];
      }

    }
  }

}

/*
  Update the last frame buffer with the current frame data
 */
void Stage::syncBuffers() {
  memcpy( &buffer_last_, &buffer_, sizeof( buffer_ ) );
}

/*
  Check if a Block b collides with the placed blocks or with stage bounds
 */
bool Stage::collides( Block *b ) {

  // Make sure the block doesn't collide with x bounds
  if( b->intersectsX( -1 ) || b->intersectsX( this->width() ) ) {
    return true;
  }

  // Make sure the block doesn't collide with y bounds
  if( b->intersectsX( -1 ) || b->intersectsY( this->height() ) ) {
    return true;
  }

  // Iterate through the block's bounds to check for collision with placed blocks
  for( int x = -2; x < 2; x++ ) {
    for( int y = -1; y < 3; y++ ) {
      
      // check if the block occupies this spot
      if( b->intersects( b->x() + x, b->y() + y ) ) {
	
	// the block occupies these coords, so check if it hits a placed block
	if ( placedBlocks_[b->y() + y][b->x() + x] != BG_COLOR ) {
	  // we hit a placed block so return true on collision check
	  return true;
	}
	
      }

    }
  }

  // didn't hit anything so return false
  return false;

}

/*
  Take a Block object and place it into the placedBlocks array
  then check if any rows need to be cleared
 */
void Stage::placeBlock( Block *block ) {

  // Iterate through the block's bounds and place all chunks 
  // that are occupied by the block into placedBlocks_
  for( int x = -2; x < 2; x++ ) {
    for( int y = -1; y < 3; y++ ) {
      
      // check if the block occupies this spot
      if( block->intersects( block->x() + x, block->y() + y ) ) {
	
	// the block occupies these coords, so set placedBlocks accordingly
	placedBlocks_[block->y() + y][block->x() + x] = block->color();
	
      }

    }
  }

}

/*
  Pushes a number of "penalty" rows up from the bottom
  Block data between 0 and numRows will be lost
 */
void Stage::pushRows( int numRows ) {

  // Push all existing rows up by numRows starting from the top of the stage and working down
  for( int y = numRows; y < this->height(); y++ ) {
    for( int x = 0; x < this->width(); x++ ) {
      // Move the block up by numrows
      // y-numRows will be 0 (top of stage) at beginning of loop
      placedBlocks_[y-numRows][x] = placedBlocks_[y][x];
    }
  }

  // Fill the newly empty rows (from height-numRows to height) with stuff
  for ( int y = this->height() - numRows; y < this->height(); y++ ) {
    for( int x = 0; x < this->width(); x++ ) {
      placedBlocks_[y][x] = 0x555555;
    }
  }

}
