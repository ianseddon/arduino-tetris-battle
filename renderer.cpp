#include "renderer.h"

Renderer::Renderer( Adafruit_ST7735 tft ) : tft_(tft) {

  // Set up TFT display
  tft_.initR( INITR_BLACKTAB );
  tft_.fillScreen( tft_.Color565( 0x00, 0x00, 0x00 ) );

  tft_.setCursor( 0, 0 );
  tft_.setTextWrap( false );

}

void Renderer::initialRender( Stage *stage ) {

  tft_.fillScreen( tft_.Color565( 0x00, 0x00, 0x00 ) );

  tft_.drawFastHLine( stage->width() * stage->blockWidth(), 15, 128, 0xCCDD00 );
  
  // draw left border
  tft_.drawFastVLine( 0, 0, 160, 0xCCDD00 );
  // draw right border
  tft_.drawFastVLine( stage->width() * stage->blockWidth(), 0, 160, 0xCCDD00 );
  // draw bottom border
  tft_.drawFastHLine( 0, stage->height() * stage->blockHeight() - 1, stage->width() * stage->blockWidth(), 0xCCDD00 );

  // draw background lines
  for( int x = 1; x < stage->width(); x++ ) {
    tft_.drawFastVLine( x * stage->blockWidth(), 0, stage->height() * stage->blockHeight() - 1, tft_.Color565( 0x22, 0x22, 0x22 ) );
  }
  for( int y = 1; y < stage->height(); y++ ) {
    tft_.drawFastHLine( 1, y * stage->blockHeight() - 1, stage->width() * stage->blockWidth() - 1, tft_.Color565( 0x22, 0x22, 0x22 ) );
  }
}

/*
  Handles the rendering for a stage object
  Only draws the difference between the two buffers
 */
void Renderer::render( Stage *stage ) {

  stage->composeBuffer();

  for( int x = 0; x < stage->width(); x++ ) {
    for( int y = 0; y < stage->height(); y++ ) {

      // draw the stage buffer
      if( stage->shouldDraw( x, y ) ) {
	tft_.fillRect( x * stage->blockWidth() + 1, y * stage->blockHeight(), stage->blockWidth() - 1, stage->blockHeight() - 1, stage->color( x, y ) );
      }
    }
  }

  stage->syncBuffers();

}

/*
  FillRect wrapper function
*/
void Renderer::fillRect( int x, int y, int w, int h, uint16_t color ) {
  tft_.fillRect( x, y, w, h, color );
}


/*
  DrawVLine wrapper function
 */
void Renderer::drawVLine( int x, int y, int h, uint16_t color ) {
  tft_.drawFastVLine( x, y, h, color );
}

/*
  DrawHLine wrapper function
*/
void Renderer::drawHLine( int x, int y, int w, uint16_t color ) {
  tft_.drawFastHLine( x, y, w, color );
}

/*
  Wrapper for tft.println that allows us to draw to a coordinate on screen with only one call
 */
void Renderer::drawText( int x, int y, const char *s ) {
  tft_.setCursor( x, y );
  tft_.print( s );
}

/*
  Wrapper for tft.println that continues to draw where the cursor was left
 */
void Renderer::drawText( const char *s ) {
  tft_.print( s );
}
