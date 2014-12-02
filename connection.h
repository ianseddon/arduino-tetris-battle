#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>

/*
  The controller for serial communcation to another arduino

  Wraps a Serial (HardwareSerial) object and handles receiving and transmitting across that port
 */

class Connection {

 public:
  Connection( HardwareSerial *serial );

  void handshakeClient();
  void handshakeServer();

  // Called every frame
  int read();

  void write( int data );

  static const int gameOverByte;

 private:
  
  HardwareSerial *serial_;

  static const int connectionRequestDelay;
  static const int connectionTimeout;

  static const char crByte;
  static const char ackByte;

};

#endif
