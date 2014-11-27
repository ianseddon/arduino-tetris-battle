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
    if( selected_ < 1 ) {
      selected_++;
      needToDraw_ = true;
    }
  }

}

void Menu::draw() {

  if( needToDraw_ ) {

    renderer_->fillRect( 35, 65, 60, 30, 0x0000 );

    // Draw the title
    renderer_->setTextSize( 2 );
    renderer_->drawText( 28, 40, "Tetris");
    renderer_->setTextSize( 1 );

    // Offset the selected text
    int offset0 = 0;
    int offset1 = 0;

    // Draw the selection pip
    switch( selected_ ) {
    case 0:
      renderer_->fillRect( 35, 68, 3, 3, 0x7E0 );
      renderer_->fillRect( 35, 83, 3, 3, 0x0000 );
      offset0 = 3;
      break;
    case 1:
      renderer_->fillRect( 35, 83, 3, 3, 0xF81F );
      renderer_->fillRect( 35, 68, 3, 3, 0x0000 );
      offset1 = 3;
      break;
    }

    // Draw the selections
    renderer_->drawText( 45 + offset0, 65, "1 player" );
    renderer_->drawText( 45 + offset1, 80, "2 player" );

    needToDraw_ = false;
  }

}
