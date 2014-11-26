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

  // Set up the display and hand it off to the renderer
  Adafruit_ST7735 tft = Adafruit_ST7735( TFT_CS, TFT_DC, TFT_RST );

  Renderer *renderer = new Renderer( tft );

  // Create the game instance (to be moved to a menu function?)
  Game *gameInstance = new Game( renderer );

  // Create the input handler
  InputHandler *inputHandler = new InputHandler();

  // Set the initial state
  state = GAME_PLAY_SINGLEPLAYER_STATE;

  // Set the time of the first frame
  // This will be updated and used to calculate
  // the delta time for each other frame
  unsigned long lastFrameTime = millis();

  // Was the game over last frame? This way we only draw the game over screen on the first frame
  bool wasGameOverLastFrame = false;

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

      // The game isn't over, so run the game loop
      if( !gameInstance->gameOver() ) {
      
	gameInstance->handleInput( inputHandler );
	gameInstance->update( frameStartTime - lastFrameTime);
	gameInstance->draw();

      }
      // The game is over, so show a game over screen
      else {

	if( !wasGameOverLastFrame ) {

	  int bannerHeight = 30;

	  // Draw the game over banner over top of the stage
	  renderer->fillRect( 1, (gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2) - (bannerHeight/2), gameInstance->stage()->width() * gameInstance->stage()->blockWidth() - 1, bannerHeight, 0x000000 );
	  renderer->drawHLine( 1, (gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2 ) - (bannerHeight / 2) - 1, gameInstance->stage()->width() * gameInstance->stage()->blockWidth() - 1, 0xCCDD00 );
	  renderer->drawHLine( 1, (gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2 ) - (bannerHeight / 2) + bannerHeight + 1, gameInstance->stage()->width() * gameInstance->stage()->blockWidth() - 1, 0xCCDD00 );

	  // Draw the game over text
	  renderer->drawText( 13, ( gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2 ) - 3, "Game Over" );
	  
	  wasGameOverLastFrame = true;

	}

	// Check if the user has pressed select to start a new game
	if( inputHandler->select() ) {
	  delete gameInstance;
	  gameInstance = new Game( renderer );
	  wasGameOverLastFrame = false;
	}

      }

      break;

    // Called each frame of the multiplayer game
    case GAME_PLAY_MULTIPLAYER_STATE:

      gameInstance->handleInput( inputHandler );
      gameInstance->update( frameStartTime - lastFrameTime );
      gameInstance->draw();
      
      break;

    }

    // Draw the FPS
    int leftPos = 85;

    char fBuf[15];
    sprintf( fBuf, "%d", (int) ( 1000 / ( frameStartTime - lastFrameTime ) ) );

    renderer->fillRect( leftPos, 0, 20, 15, 0x000000 );
    renderer->drawText( leftPos, 3, fBuf );
    renderer->drawText( "fps" );

    sprintf( fBuf, "%d", gameInstance->block()->x() );

    renderer->fillRect( leftPos, 25, 20, 15, 0x000000 );
    renderer->drawText( leftPos, 25, "x:" );
    renderer->drawText( fBuf );

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
