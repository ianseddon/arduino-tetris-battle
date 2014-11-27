#ifndef MENU_H
#define MENU_H

#include "input.h"
#include "renderer.h"

class Menu {
 public:

  // Constructor
  Menu( Renderer *renderer );

  // Handle the input
  void handleInput( InputHandler *ih );
  void draw();

  int selected() const { return selected_; }

 private:

  // The pointer to our renderer
  Renderer *renderer_;

  // The index of the option we have selected
  int selected_;

  // Do we need to draw?
  bool needToDraw_;

};

#endif
