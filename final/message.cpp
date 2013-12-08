/* Filename: message.cpp 
   Associated implementation file: message.h */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 6th November 2012 */

/* This implementation file contains all function definitions
   for the Message class defined in header file 'message.h'. */


#include <iostream>

#include "message.h"

using namespace std;


/* BEGIN FUNCTION DEFINITION */
Message::Message( const string &t, const int s, const int d ) {
  the_text = t;
  source = s;
  destination = d;
}
/* END CONSTRUCTOR DEFINITION */


/* BEGIN FUNCTION DEFINITION */
string Message::getMessage() const {
  return the_text;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
int Message::getSource() const {
  return source;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
int Message::getDestination() const {
  return destination;
}
/* END FUNCTION DEFINITION */
