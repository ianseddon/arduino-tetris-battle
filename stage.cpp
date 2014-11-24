#include "stage.h"

Stage::Stage() {
  memset( blockBuffer_, 0x000000, sizeof( blockBuffer_ ) );
  memset( blockBuffer_last_, 0x000000, sizeof( blockBuffer_last_ ) );
}
