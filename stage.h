#ifndef STAGE_H
#define STAGE_H

#include <Arduino.h>
//#include "block.h"

// Stage width / height in number of blocks
const int STAGE_WIDTH = 10;
const int STAGE_HEIGHT = 20;

// Block size in pixels
const int BLOCK_WIDTH = 8;
const int BLOCK_HEIGHT = 8;

class Stage {

 public:

  Stage();

  // Did a buffer value change this frame?
  bool shouldDraw( int x, int y ) { return ( blockBuffer_[y][x] != blockBuffer_last_[y][x] ); }

  // Getters for the buffer values
  uint16_t getColor( int x, int y ) const { return blockBuffer_[y][x]; }
  void setColor( int x, int y, uint16_t c ) { blockBuffer_[y][x] = c; }
  //uint16_t blockBuffer_last( int x, int y ) { return blockBuffer_last_[y][x]; }

  // Update buffer
  void updateBuffer();

  // "Getters" for the const height/width values
  int width() const { return STAGE_WIDTH; }
  int height() const { return STAGE_HEIGHT; }
  int blockWidth() const { return BLOCK_WIDTH; }
  int blockHeight() const { return BLOCK_HEIGHT; }

 private:
  
  // The buffers for the controlled block -- REPLACE WITH A BLOCK INSTANCE
  //uint16_t cBlockBuffer_front[STAGE_HEIGHT][STAGE_WIDTH];
  //uint16_t cBlockBuffer_back[STAGE_HEIGHT][STAGE_WIDTH];

  //Block *controlledBlock_;

  // The buffer for the placed blocks
  uint16_t blockBuffer_[STAGE_HEIGHT][STAGE_WIDTH];
  // The buffer for the placed blocks in the previous frame
  uint16_t blockBuffer_last_[STAGE_HEIGHT][STAGE_WIDTH];

};

#endif
