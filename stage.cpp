#include "stage.h"

Stage::Stage() {
  // Set the memory for the block buffers
  memset( blockBuffer_, 0x000000, sizeof( blockBuffer_ ) );
  memset( blockBuffer_last_, 0x000000, sizeof( blockBuffer_last_ ) );
}

void Stage::updateBuffer() {
  memcpy( &blockBuffer_last_, &blockBuffer_, sizeof( blockBuffer_ ) );
}
