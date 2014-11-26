/*
  Block Class (aka Tetromino)
  ---------------------------
  Represents a single Tetronimo
  or block, and holds all the information
  about the physical data of the Tetronimo, 
  and graphical representation of the block.

  Also contains helper functions 
  for determining the intersections
  and collisions of the block
 */
#ifndef BLOCK_H
#define BLOCK_H

#include <Arduino.h>

//const int BLOCK_WIDTH = 8;
//const int BLOCK_HEIGHT = 8;

const uint16_t colors[7] = {
  0xFFE0,//0xFFFF00,//0xFFFF00, // O Block
  0x7FF,//0x00FFFF, // I Block
  0x7E0,//0x00FF00, // S Block
  0xF800,//0xFF0000, // Z Block
  0xFBE0,//0xFFA500, // L Block
  0x1F,//0x0000FF, // J Block
  0xF81F//0xA020F0  // T Block
};


const int OBlock = 0;
const int IBlock = 1;
const int SBlock = 2;
const int ZBlock = 3;
const int LBlock = 4;
const int JBlock = 5;
const int TBlock = 6;

class Block {
public:

  // The constructor
  Block( int x, int y, uint16_t color, int shape ) : x_(x), y_(y), color_(color), shape_(shape) {
    rotated_ = 0;
  }

  /*
    Getters and setters for the parameters
   */

  void x( int x ) { lastX_ = x_; x_ = x; }
  int x() const { return x_; }

  void y( int y ) { lastY_ = y_; y_ = y; }
  int y() const { return y_; }

  int lastX() const { return lastX_; }
  int lastY() const { return lastY_; }

  void color( uint16_t c ) { color_ = c; }
  uint16_t color() const { return color_; }

  void shape( int shape ) { shape_ = shape; }
  int shape() const { return shape_; }

  void rotated( int rotated ) { rotated_ = rotated; }
  int rotated() const { return rotated_; }

  /*
    Block functionality
   */

  void rotate();
  void unrotate();

  /*
    Helper functions
   */

  bool intersects( int x, int y );

  bool intersectsX( int x );
  bool intersectsY( int y );
  
private:
  int x_;
  int y_;
  int lastX_;
  int lastY_;
  uint16_t color_;
  int shape_;
  int rotated_;
};

#endif
