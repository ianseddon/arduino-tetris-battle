#include "stage.h"

Stage::Stage() {
  // Set the memory for the block buffers
  memset( blockBuffer_, 0x000000, sizeof( blockBuffer_ ) );
  memset( blockBuffer_last_, 0x000000, sizeof( blockBuffer_last_ ) );
}

bool Stage::shouldDraw( int x, int y ) {
  return ( blockBuffer_[y][x] != blockBuffer_last_[y][x] || ( block_->intersects(x, y) ));
}

uint16_t Stage::color( int x, int y ) const {

  // Check if the block pointer is assigned
  if( block_ ) {
    Serial.print("block pointer set");
    if( block_->intersects( x, y ) ) return block_->color();
  }

  return blockBuffer_[y][x];
}

void Stage::syncBuffers() {
  memcpy( &blockBuffer_last_, &blockBuffer_, sizeof( blockBuffer_ ) );
}
