#ifndef STAGE_H
#define STAGE_H

#include <Arduino.h>
//#include "block.h"

const int STAGE_WIDTH = 10;
const int STAGE_HEIGHT = 20;

class Stage {

 public:

  Stage();

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
