/* Filename: message.h 
   Associated implementation file: message.cpp */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 6th November 2012 */

/* This header file contains the class definition for Message
 including all the attributes and member functions. It packages
 a Message object which can be passed through a network of Hosts
 and Routers to a destination Host. */


# ifndef MESSAGE_H
# define MESSAGE_H

#include <string>

using namespace std;

class Message {
 private:
  
  string the_text;
  int source, destination;


 public:

  Message( const string &t, const int s, const int d ); //constructor


  /* getMessage() returns the message text as a string. */

  string getMessage() const;


  /* getSource() returns the integer address of the source Host */

  int getSource() const;


  /* getDestination() returns the integer address of the destination
     Host */

  int getDestination() const;

};

#endif
