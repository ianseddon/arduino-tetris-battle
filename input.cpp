#include "input.h"
#include <Arduino.h>

InputHandler::InputHandler() {

  // Set up pins for joystick
  pinMode(JOYSTICK_SEL, INPUT);
  digitalWrite(JOYSTICK_SEL, HIGH);

  // Read the base input values
  hInputBase_ = analogRead( JOYSTICK_HORIZ );
  vInputBase_ = analogRead( JOYSTICK_VERT  );
}

void InputHandler::readInput( ) {

  int hInput = analogRead( JOYSTICK_HORIZ );
  int vInput = analogRead( JOYSTICK_VERT  );
  int sInput = digitalRead( JOYSTICK_SEL  );

  // reset the input values
  left_ = false;
  right_ = false;
  up_ = false;
  down_ = false;
  select_ = false;

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
  if( sInput == LOW  )
    select_ = true;
}
