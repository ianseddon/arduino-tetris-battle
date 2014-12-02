#include "menu.h"

Menu::Menu( Renderer *renderer ) : renderer_(renderer) {

  selected_ = 0;

  needToDraw_ = true;

}

void Menu::handleInput( InputHandler *ih ) {

  if( ih->up() ) {
    if( selected_ > 0 ) {
      selected_--;
      needToDraw_ = true;
    }
  }
  
  if( ih->down() ) {
    if( selected_ < 2 ) {
      selected_++;
      needToDraw_ = true;
    }
  }

}

void Menu::redraw() {
  needToDraw_ = true;
  draw();
}

void Menu::draw() {

  if( needToDraw_ ) {

    int leftBound = 25;

    renderer_->fillRect( leftBound, 65, 128 - leftBound, 50, 0x0000 );

    // Draw the title
    renderer_->setTextSize( 2 );
    renderer_->drawText( 28, 40, "Tetris");
    renderer_->setTextSize( 1 );


    // Offset the selected text
    int offset0 = 10;
    int offset1 = 10;
    int offset2 = 10;

    // Draw the selection pip
    switch( selected_ ) {
    case 0:
      // Draw selection pip
      renderer_->fillRect( leftBound, 68, 3, 3, 0x7E0 );
      // Erase unselected pips
      renderer_->fillRect( leftBound, 83, 3, 3, 0x0000 );
      renderer_->fillRect( leftBound, 98, 3, 3, 0x0000 );
      offset0 = 13;
      break;
    case 1:
      // Draw selection pip
      renderer_->fillRect( leftBound, 83, 3, 3, 0xF81F );
      // Erase unselected pips
      renderer_->fillRect( leftBound, 68, 3, 3, 0x0000 );
      renderer_->fillRect( leftBound, 98, 3, 3, 0x0000 );
      offset1 = 13;
      break;
    case 2:
      // Draw selection pip
      renderer_->fillRect( leftBound, 98, 3, 3, 0xF81F );
      // Erase unselected pips
      renderer_->fillRect( leftBound, 68, 3, 3, 0x0000 );
      renderer_->fillRect( leftBound, 83, 3, 3, 0x0000 );
      offset2 = 13;
      break;
    }

    // Draw the selections
    renderer_->drawText( leftBound + offset0, 65, "1 player" );
    renderer_->drawText( leftBound + offset1, 80, "2 player (host)" );
    renderer_->drawText( leftBound + offset2, 95, "2 player (join)" );

    needToDraw_ = false;
  }

}
