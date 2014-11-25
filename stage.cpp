#include "stage.h"

Stage::Stage() {

  // Set the memory for the placed blocks
  memset( placedBlocks_, 0x000000, sizeof( placedBlocks_ ) );

  // Set the memory for the buffers
  memset( buffer_, 0x000000, sizeof( buffer_ ) );
  memset( buffer_last_, 0x000000, sizeof( buffer_last_ ) );

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
