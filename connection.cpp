#include "connection.h"

const int Connection::connectionRequestDelay = 1000;
const int Connection::connectionTimeout = 1000;
const char Connection::crByte = 'C';
const char Connection::ackByte = 'A';

Connection::Connection( HardwareSerial *serial ) : serial_(serial) {

  serial->begin( 9600 );

}

/*
  Do handshake
 */
void Connection::handshakeServer() {
  
  while( 1 ) {

    // Wait until receiving a response
    while( !serial_->available() ) {}

    char receivedByte = (char) serial_->read();

    // Received a connection request
    if( receivedByte == crByte ) {
      
      // Send acknowledgement
      serial_->write( ackByte );

      unsigned long ackTime = millis();

      // wait until we time out to receive acknowledgement
      while( millis() - ackTime < connectionTimeout ) {

	if( serial_->available() ) {

	  // Read received byte
	  receivedByte = (char) serial_->read();

	  if( receivedByte == ackByte ) {
	    return;
	  }

	}

      }

    }

  }

}

void Connection::handshakeClient() {
  
  unsigned long crTime = millis();

  while( 1 ) {

    // Send a connection request repeatedly until receiving a response

    while( !serial_->available() ) {

      // Have we waited long enough to send another connection request?
      if( millis() - crTime > connectionRequestDelay ) {
	serial_->write( crByte );
	crTime = millis();
      }

    }

    // We've received a byte
    char receivedByte = (char) serial_->read();

    // Check if we've received an acknowledgment byte
    if( receivedByte == ackByte ) {

      // Send acknowledgment that we completed handshake
      serial_->write( ackByte );

      break;

    }

  }

}

int Connection::read() {
  return (int) serial_->read();
}
