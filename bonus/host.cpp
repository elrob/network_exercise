/* Filename: host.cpp 
   Associated header file: host.h */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 6th November 2012 */

/* This implementation file contains all function definitions
   for the Host class defined in header file 'host.h'. */


#include <iostream>

using namespace std;

#include "host.h"

/* BEGIN CONSTRUCTOR DEFINITON */
Host::Host( const int a ) {
  address = a;
  parent = NULL;
}
/* END CONSTRUCTOR DEFINITION */


/* BEGIN FUNCTION DEFINITION */
int Host::getAddress() {
  return address;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Host::setParent( Router *p ) {
  parent = p;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
Router* Host::getParent() {
  return parent;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Host::print_parent() {
  cout << "Host " << address << " is connected to parent Router ";
  ( parent == NULL ? cout << "NULL" : cout << parent->getAddress() );
  cout << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Host::send( const int dest, const string &text ) {
  Message the_message( text, this->address, dest );   // create message
  cout << "Host " << address << " sent a message to Host " << dest << ": " << text << endl << endl;
  if ( parent != NULL )
    parent->send( the_message );
  else
    cout << "Failed to send message from Host " << this->address 
	 << " because it is not connected to a router.\n" << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Host::receive( const Message &m ) {
  cout << "Host " << address << " received a message from Host " << m.getSource() 
       << ": " << m.getMessage() << endl << endl;
}
/* END FUNCTION DEFINITION */


