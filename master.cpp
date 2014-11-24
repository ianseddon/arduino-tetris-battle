#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Include our class files
#include "game.h"
#include "input.h"

#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  8

uint8_t state;

const uint8_t MENU_STATE                   = 0;
const uint8_t GAME_PLAY_SINGLEPLAYER_STATE = 1;
const uint8_t GAME_PLAY_MULTIPLAYER_STATE  = 2;

void setup() {

  // Set up serial logging
  Serial.begin(9600);

  // Create the game instance (to be moved to a menu function?)
  Game *gameInstance = new Game();

  // Create the input handler
  InputHandler *inputHandler = new InputHandler( );

  /*
    The main gameloop

    Handles state switching based on "state" variable,
    then calls the appropriate handler functions based
    on which state it is in each frame.
  */
  while( 1 ) {

    // Read the input every frame
    inputHandler->readInput( );

    switch ( state ) {

    // Called each frame of the menu state
    case MENU_STATE:
      
      break;

    // Called each frame of the singleplayer game
    case GAME_PLAY_SINGLEPLAYER_STATE:

      gameInstance->handleInput( inputHandler );
      gameInstance->update();
      gameInstance->draw();

      break;

    // Called each frame of the multiplayer game
    case GAME_PLAY_MULTIPLAYER_STATE:

      gameInstance->handleInput( inputHandler );
      gameInstance->update();
      gameInstance->draw();

      break;

  }

  }

  // Dealloc objects
  delete gameInstance;
  delete inputHandler;

}

// Not used, since we can't control this as well as our own while loop
void loop() {

}
