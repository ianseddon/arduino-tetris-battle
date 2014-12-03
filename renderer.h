/*
  Renderer
  ------------------
  Takes game objects and displays them to screen
  Also handles all drawing calls for anything else 
  that might need to be displayed

  Wraps an instance of the Adafruit TFT object,
  could be easily ported to a different rendering medium
  by changing Adafruit TFT specific library functions
  to say OpenGL rendering functions or another framework
 */
#ifndef RENDERER_H
#define RENDERER_H

//#include "block.h"
#include "stage.h"

/*
  Hardware specific definitions
  and includes for Adafruit TFT LCD
*/

#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  8

class Renderer {
 public:

  // Constructor
  Renderer( Adafruit_ST7735 tft );

  // Drawing functions
  void initialRender( Stage *stage );
  void render( Stage *stage );

  void wipeScreen();

  // Wrappers for Adafruit drawing functions for easy portability
  void fillRect( int x, int y, int w, int h, uint16_t color );
  void drawVLine( int x, int y, int h, uint16_t color );
  void drawHLine( int x, int y, int w, uint16_t color );
  void drawText( int x, int y, const char *s );
  void drawText( const char *s );
  void drawText( float f );
  void setTextSize( int s );

 private:

  Adafruit_ST7735 tft_;

};

#endif
