#include <Arduino.h>

// Include our class files
#include "game.h"
#include "input.h"

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
  InputHandler *inputHandler = new InputHandler();

  // Set the initial state
  state = GAME_PLAY_SINGLEPLAYER_STATE;

  // Set the time of the first frame
  // This will be updated and used to calculate
  // the delta time for each other frame
  unsigned long lastFrameTime = millis();

  /*
    The main gameloop

    Handles state switching based on "state" variable,
    then calls the appropriate handler functions based
    on which state it is in each frame.
  */
  while( 1 ) {

    // Read the input every frame
    inputHandler->readInput( );

    // The time at start of frame
    unsigned long frameStartTime = millis();

    switch ( state ) {
      
    // Called each frame of the menu state
    case MENU_STATE:
      
      break;
      
    // Called each frame of the singleplayer game
    case GAME_PLAY_SINGLEPLAYER_STATE:
      
      gameInstance->handleInput( inputHandler );
      gameInstance->update( frameStartTime - lastFrameTime );
      gameInstance->draw();

      break;

    // Called each frame of the multiplayer game
    case GAME_PLAY_MULTIPLAYER_STATE:

      gameInstance->handleInput( inputHandler );
      gameInstance->update( frameStartTime - lastFrameTime );
      gameInstance->draw();
      
      break;

    }

    // Update lastFrameTime
    lastFrameTime = frameStartTime;

    // Delay to enforce a frame delay
    delay( 10 );

  }

  // Dealloc objects
  delete gameInstance;
  delete inputHandler;

}

// Not used, since we can't control this as well as our own while loop
void loop() {

}
