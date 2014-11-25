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

void Stage::composeBuffer() {
  
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

void Stage::syncBuffers() {
  memcpy( &buffer_last_, &buffer_, sizeof( buffer_ ) );
}

/*
  Check if a Block b collides with the placed blocks
 */
bool Stage::collides( Block *b ) {
  
  // Iterate through the block's bounds
  for( int x = -2; x < 2; x++ ) {
    for( int y = -1; y < 3; y++ ) {
      
      // check if the block occupies this spot
      if( b->intersects( b->x() + x, b->y() + y ) ) {
	
	// the block occupies these coords, so check if it hits a placed block
	if ( placedBlocks_[y][x] != BG_COLOR ) {
	  // we hit a placed block so return true on collision check
	  return true;
	}
	
      }

    }
  }

  // didn't hit anything so return false
  return false;

}
