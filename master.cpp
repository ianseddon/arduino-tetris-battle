#include <Arduino.h>

// Include our class files
#include "game.h"
#include "input.h"
#include "menu.h"
#include "connection.h"

uint8_t state;

const uint8_t MENU_STATE                    = 0;
const uint8_t GAME_PLAY_SINGLEPLAYER_STATE  = 1;
const uint8_t GAME_PAUSE_SINGLEPLAYER_STATE = 3;
const uint8_t GAME_PLAY_MULTIPLAYER_STATE   = 2;

// Was the game over last frame? This way we only draw the game over screen on the first frame
bool wasGameOverLastFrame = false;

// Delay showing the FPS to reduce flicker
unsigned long lastDrewFPS;

// Set up the display
Adafruit_ST7735 tft = Adafruit_ST7735( TFT_CS, TFT_DC, TFT_RST );

// The pointers to our renderer and gameInstance
Game *gameInstance;
Renderer *renderer;
InputHandler *inputHandler;
Menu *menu;

Connection *connection;
Connection *nulcon;

void startSinglePlayerGame() {
  
  // Dealloc old game
  if( gameInstance ) delete gameInstance;

  // Create a new game
  gameInstance = new Game( renderer, nulcon );

  // Mark the game as not over
  wasGameOverLastFrame = false;

  // Set the state to singleplayer game state
  state = GAME_PLAY_SINGLEPLAYER_STATE;
}

void startMultiPlayerGame() {
  
  // Dealloc old game
  if( gameInstance ) delete gameInstance;

  // Create a new game
  gameInstance = new Game( renderer, connection );

  // Mark the game as not over
  wasGameOverLastFrame = false;
  
  // Set the state to multiplayer game state
  state = GAME_PLAY_MULTIPLAYER_STATE;

}

// Draw the FPS
void drawFPS( unsigned long dt ) {

  // Only draw every 50ms to reduce flickering
  if( millis() - lastDrewFPS < 50 ) return;

  int leftPos = 85;

  char fBuf[15];
  sprintf( fBuf, "%d", (int) ( 1000 / dt ) );
  
  renderer->fillRect( leftPos, 0, 50, 15, 0x000000 );
  renderer->drawText( leftPos, 3, fBuf );
  renderer->drawText( "fps" );

  lastDrewFPS = millis();
}

// Draw the game over banner
void drawBanner( const char * text ) {
  int bannerHeight = 30;

  // Draw the game over banner over top of the stage
  renderer->fillRect( 1, (gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2) - (bannerHeight/2), gameInstance->stage()->width() * gameInstance->stage()->blockWidth() - 1, bannerHeight, 0x000000 );
  renderer->drawHLine( 1, (gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2 ) - (bannerHeight / 2) - 1, gameInstance->stage()->width() * gameInstance->stage()->blockWidth() - 1, 0xCCDD00 );
  renderer->drawHLine( 1, (gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2 ) - (bannerHeight / 2) + bannerHeight + 1, gameInstance->stage()->width() * gameInstance->stage()->blockWidth() - 1, 0xCCDD00 );
  
  // Draw the game over text
  renderer->drawText( 13, ( gameInstance->stage()->height() * gameInstance->stage()->blockHeight() / 2 ) - 3, text );
}

void drawWait() {
  renderer->wipeScreen();
  renderer->drawText( 35, 72, "Waiting..." );
}

void setup() {

  // Set up serial logging
  Serial.begin(9600);

  // Generate a randomized seed for the generation of blocks
  uint16_t generatedSeed = 0;
  for ( uint32_t i = 0; i < 16; i++ ) {
    generatedSeed += analogRead(10) & 1;
    generatedSeed <<= 1;
    delay(3);
  }
  // Seed the random generation of blocks
  randomSeed( generatedSeed );

  // Create the renderer and hand off the display reference to it
  renderer = new Renderer( tft );

  // Create the menu and hand the renderer reference to it
  menu = new Menu( renderer );

  // Create the input handler
  inputHandler = new InputHandler();

  // Create the connection controller
  connection = new Connection( &Serial3 );

  // Create a null connection to pass to singleplayer games
  nulcon = new Connection( NULL );

  // Set the initial state
  state = MENU_STATE;

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

    // Differ logic based on game state
    switch ( state ) {
      
    // Called each frame of the menu state
    case MENU_STATE:

      // Read the input
      menu->handleInput( inputHandler );

      // Draw the menu
      menu->draw();

      if( inputHandler->select() ) {

	// Take the appropriate action depending on which was selected
	switch( menu->selected() ) {
	// Starting a single player game
	case 0:
	  startSinglePlayerGame();
	  break;
	// Starting a two player game (host)
	case 1:
	  drawWait();
	  connection->handshakeServer();
	  startMultiPlayerGame();
	  break;
	// Starting a two player game (join)
	case 2:
	  drawWait();
	  connection->handshakeClient();
	  startMultiPlayerGame();
	  break;
	}

      }

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

	  drawBanner( "Game Over" );
	  
	  wasGameOverLastFrame = true;

	}

	// Check if the user has pressed select to start a new game
	if( inputHandler->select() ) {
	  state = MENU_STATE;
	  menu->redraw();
	}

      }

      break;

    case GAME_PAUSE_SINGLEPLAYER_STATE:
      break;

    // Called each frame of the multiplayer game
    case GAME_PLAY_MULTIPLAYER_STATE:

      if( !gameInstance->gameOver() ) {
	gameInstance->handleInput( inputHandler );
	gameInstance->update( frameStartTime - lastFrameTime );
	gameInstance->draw();
      }
      else {

	// Only draw for the first frame of game over state to avoid unnecessary draws
	if( !wasGameOverLastFrame ) {

	  // Display a game won message
	  if( gameInstance->won() ) {
	    drawBanner( "You Win!");
	  }
	  // Display a game lost message
	  else {
	    drawBanner( "You Lost :(" );
	  }

	  // Send the game over byte to the other player
	  connection->write( Connection::gameOverByte );

	  // Make sure we know the game was over last frame
	  wasGameOverLastFrame = true;

	}

	// Check if the user has pressed select to start a new game
	if( inputHandler->select() ) {
	  state = MENU_STATE;
	  menu->redraw();
	}

      }
      break;

    }

    int dt = frameStartTime - lastFrameTime;

    if( state != MENU_STATE )
      drawFPS( dt );

    // Delay to enforce a constant frame rate
    //delay( max( 30 - dt, 0 ) );
    delay( 30 );

    // Update lastFrameTime
    lastFrameTime = frameStartTime;

  }

  // Dealloc objects
  delete gameInstance;
  delete inputHandler;
  delete renderer;
  delete menu;

}

// Not used, since we can't control this as well as our own while loop
void loop() {

}
