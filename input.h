/*
  Input Handler Class
  -------------------------------------------
  Encapsulates all user input for this frame
  into an easily parsable data structure that
  can be passed to each state handler class
 */
#ifndef INPUT_H
#define INPUT_H

// The ports to read for the joystick
const int JOYSTICK_VERT      = 0;
const int JOYSTICK_HORIZ     = 1;
const int JOYSTICK_SEL       = 9;

// The dead zone to take into account when reading the joystick
const int JOYSTICK_DEAD_ZONE = 10;

class InputHandler {

 public:

  // Constructor
 InputHandler( int hInputBase, int vInputBase ) : hInputBase_(hInputBase), vInputBase_(vInputBase) {}

  // Read the input for this frame
  void readInput( int hInput, int vInput, int sInput );

  // Getters and setters
  bool left() const { return left_; }
  bool right() const { return right_; }
  bool up() const { return up_; }
  bool down() const { return down_; }
  bool select() const { return select_; }

 private:
  
  bool left_;  // Joystick left pressed
  bool right_; // Joystick right pressed
  bool up_;    // Joystick up pressed
  bool down_;  // Joystick down pressed
  bool select_;// Joystick select pressed

  int hInputBase_; // Base value for horizontal axis
  int vInputBase_; // Base value for vertical axis

};

void InputHandler::readInput( int hInput, int vInput, int sInput) {

  // reset the input values
  left_ = false;
  right_ = false;
  up_ = false;
  down_ = false;

  // If joystick is pressed down
  if( vInput > vInputBase_ + JOYSTICK_DEAD_ZONE )
    down_ = true;

  // Otherwise, check if joystick is pressed up
  else if( vInput < vInputBase_ - JOYSTICK_DEAD_ZONE )
    up_ = true;

  // If joystick is pressed left
  if( hInput < hInputBase_ - JOYSTICK_DEAD_ZONE )
    left_ = true;

  // Otherwise, check if joystick is pressed right
  else if( hInput > hInputBase_ + JOYSTICK_DEAD_ZONE )
    right_ = true;

  // Check if select is pressed
  if( sInput == 0 )
    select_ = true;
}

#endif
