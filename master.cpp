#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Include our class files
#include "input.h"
#include "block.h"

#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  8

uint8_t state;

const uint8_t MENU_STATE                   = 0;
const uint8_t GAME_PLAY_SINGLEPLAYER_STATE = 1;
const uint8_t GAME_PLAY_MULTIPLAYER_STATE  = 2;

void setup() {

  // Set up pins for joystick select
  pinMode(JOYSTICK_SEL, INPUT);
  digitalWrite(JOYSTICK_SEL, HIGH);
  // Create the input handler
  InputHandler *inputHandler = new InputHandler( analogRead(JOYSTICK_HORIZ), analogRead(JOYSTICK_VERT) );

  /*
    The main gameloop

    Handles state switching based on "state" variable,
    then calls the appropriate handler functions based
    on which state it is in each frame.
  */
  while( 1 ) {

    // Read the input every frame
    inputHandler->readInput( analogRead(JOYSTICK_HORIZ), analogRead(JOYSTICK_VERT), digitalRead(JOYSTICK_SEL) );

    switch ( state ) {

    // Called each frame of the menu state
    case MENU_STATE:
      
      break;

    // Called each frame of the singleplayer game
    case GAME_PLAY_SINGLEPLAYER_STATE:
      
      break;

    // Called each frame of the multiplayer game
    case GAME_PLAY_MULTIPLAYER_STATE:
      
      break;

  }

  }

}

// Not used, since we can't control this as well as our own while loop
void loop() {

}
