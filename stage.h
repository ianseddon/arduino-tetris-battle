/*
  Stage Controller
  -----------------------------
  Handles all the logic relating
  to the physical representation
  of the blocks on the game area
  and composes the data into a buffer
  to be rendered by the Renderer

  Buffer format:
   Array of 16 bit unsigned integers
   representing the block colors for
   that position on the stage
 */
#ifndef STAGE_H
#define STAGE_H

#include <Arduino.h>
#include "block.h"

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
  bool shouldDraw( int x, int y );

  // Compose the buffer for this frame from stage and block data
  void composeBuffer();

  // Copy this frame's buffer to last frame buffer
  void syncBuffers();

  // Clearing rows, returns number of rows cleared
  int clearRows( int block_y );
  
  // Placing blocks, returns number of rows cleared (if any)
  int placeBlock( Block *block ); // calls clear rows
  
  // Pushing rows
  void pushRows( int numRows );

  // Collision detection
  bool collides( Block *block );


  // Getters for the buffer values
  uint16_t color( int x, int y ) const { return buffer_[y][x]; };
  void color( int x, int y, uint16_t c ) { buffer_[y][x] = c; }

  // Setter for block
  void block( Block *block ) { this->block_ = block; };

  // "Getters" for the const height/width values
  int width() const { return STAGE_WIDTH; }
  int height() const { return STAGE_HEIGHT; }
  int blockWidth() const { return BLOCK_WIDTH; }
  int blockHeight() const { return BLOCK_HEIGHT; }

 private:

  // Pointer to the currently controlled block
  Block *block_;

  // Placed blocks
  uint16_t placedBlocks_[STAGE_HEIGHT][STAGE_WIDTH];

  // The buffer for the stage
  uint16_t buffer_[STAGE_HEIGHT][STAGE_WIDTH];
  // The buffer for the stage in the previous frame
  uint16_t buffer_last_[STAGE_HEIGHT][STAGE_WIDTH];

};

#endif
