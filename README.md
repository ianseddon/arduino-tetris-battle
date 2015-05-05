# arduino-tetris-battle
Tetris! With a friend! (Or not) 

This project is an implementation of Tetris on the Arduino, with a twist. If you have a second Arduino, you can connect them via the TX3 and RX3 serial ports, and play battle Tetris, with one Arduino acting as the server, and the other as the client.
Battle Tetris functions as traditional Tetris, but when you get a combo (one or more rows cleared in succession), you send that a number of lines to your opponent equal to the number of line-clears you've completed in succession. Be careful though, giving your opponent more lines to clear can backfire if they can clear them all in a row and send even more back to you!
One of the goals of this project was to make it easily portable to another platform, hence the abstraction and loose coupling of hardware and platform specific functionality.

## Setup
The Arduino is wired exactly as shown in the link below. 

http://ugweb.cs.ualberta.ca/~c274/web/ConcreteComputing/section/adafruit_lcd.htm

This project uses an Adafruit TFT display (120x160) and the Adafruit graphics library, however this project could be ported to another graphics device/library easily with changes to the Renderer class.

If you wish to change the wiring of the joystick, the ports are defined in "input.h".

If you wish to change the wiring of the display, the ports are defined in "renderer.h"

## Building
Ensure that your Arduino is connected via its serial port, then run "make upload" in your terminal from the project source directory.

"make clean" can be used to clean files left from previous uses of the "make" command. If "make upload" is having problems after you have made changes, try a "make clean"
