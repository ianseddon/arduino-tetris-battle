#include "block.h"

int Blocks[7][4][4][4] = {
  /*
    O Block
  */
  {
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    }
  },
  /*
    I Block
  */
  {
    {
      { 0, 0, 0, 0 },
      { 1, 1, 1, 1 },
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 }
    }
  },
  /*
    S Block
  */
  {
    {
      { 0, 0, 0, 0 },
      { 0, 0, 1, 1 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 1 },
      { 0, 0, 0, 1 },
      { 0, 0, 0, 0 }
    }
  },
  /*
    Z Block
   */
  {
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 1 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 0, 1 },
      { 0, 0, 1, 1 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    }
  },
  /*
    L Block
   */
  {
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 1, 0, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 1 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 0, 1 },
      { 0, 1, 1, 1 },
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 1, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    }
  },
  /*
    J Block
   */
  {
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 0, 0, 1 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 1 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 1, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    }
  },
  /*
    T Block
  */
  {
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 1 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    },
    {
      { 0, 0, 1, 0 },
      { 0, 1, 1, 1 },
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
    },
    {
      { 0, 0, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    }
  }
};

bool Block::intersects( int x, int y ) {

  // if we're checking intersection with the origin, always return true
  if( x == x_ && y == y_ ) return true;
  else {

    // set relative coordinates for convenience, and shift them to be 0 to 3
    int lx = x - x_;
    int ly = y - y_;

    // outer limits of blocks are
    // x-2, x+1
    // y-1, y+2
    // so if we go outside this bounding box, return no intersection
    if( lx < -2 || lx > 1 || ly < -1 || ly > 2 ) return false;
    // otherwise check vs bounding boxes
    else {
      // shift the relative x values to be 0 to 3 so we can check them vs array
      ly += 1;
      lx += 2;
      if( Blocks[this->shape()][this->rotated()][ly][lx] ) return true;
      else return false;
    }

  }

}

bool Block::intersectsX( int x ) {
  int lx = x - x_;
  
  // check if we're in bounds, and then shift relative coords to be within array bounds
  if( lx < -2 || lx > 1 ) return false;
  else lx += 2;

  bool intersects = false;

  // if we're in bounds, check along that column for intersection
  for( int y = 0; y < 4; y++ ) {
    // check the current y value for intersection
    if( Blocks[this->shape()][this->rotated()][y][lx] ) {
      intersects = true;
      break;
    }
  }
  
  return intersects;
}

bool Block::intersectsY( int y ) {
  int ly = y - y_;

  // check if we're in bounds, and then shift relative coords to be within array bounds
  if( ly < -1 || ly > 2 ) return false;
  else ly += 1;

  bool intersects = false;

  // if we're in bounds, check along that row for intersection
  for( int x = 0; x < 4; x++ ) {
    // check the current x value for intersection
    if( Blocks[this->shape()][this->rotated()][ly][x] ) {
      intersects = true;
      break;
    }
  }
  
  return intersects;
}

void Block::rotate() {
  int numRotations = 2;

  // check if we're rotating a block with more than two states
  if( shape_ == LBlock || shape_ == JBlock || shape_ == TBlock ) numRotations = 4;

  // change the collision matrix index to the next rotation, and wrap around after numRotations
  rotated_ = (rotated_ + 1) % numRotations;
}

void Block::unrotate() {
  int numRotations = 2;

  // check if we're unrotating a block with more than two states
  if( shape_ == LBlock || shape_ == JBlock || shape_ == TBlock ) numRotations = 4;
  
  // change the collision matrix index to the previous rotation, and wrap around at 0
  rotated_ = (rotated_ + numRotations - 1) % numRotations;
}
