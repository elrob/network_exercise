/* Filename: host.h 
   Associated implementation file: host.cpp */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 5th November 2012 */

/* This header file contains the class definition for Host
 including all the attributes and member functions. It enables
 the Host to form part of a network of Hosts and Routers through 
 which messages can be passed from Host to Host via Routers. */

# ifndef HOST_H
# define HOST_H

#include "router.h"
#include "message.h"

class Router;

class Host {
 private:
  
  int address;
  Router *parent;


 public:
  
  Host( const int a ); //constructor


  /* getAddress() returns the integer address
     of the Host object. */

  int getAddress(); 


  /* setParent( Router *p ) sets the host attribute 'parent' 
     to the Router pointer 'p'. */

  void setParent( Router *p ) ;


  /* getParent() returns Router pointer attribute 'parent'. */

  Router* getParent();


  /* print_parent() outputs the address of the 'parent' Router
     to the console output stream to aid testing and debugging. */

  void print_parent();


  /* send(...) creates an object of class Message. The string 
     'text', the source address (the Host's own address) and the 
     destination address 'dest' are used to initialise the Message.
     It outputs to the console output stream to indicate that the 
     Message is to be sent from one Host to another. If a 'parent' 
     exists (the Host is connected to a Router), it then calls the 
     Router 'send' function on that Router. Else it fails to send 
     and outputs a Message to the console output stream. */

  void send( const int dest, const string &text );


  /* receive(...) is used by the parent Router to pass an incoming
     Message to the Host if the Host's address is the destination. 
     It outputs to the console output stream to indicate that the 
     Message has reached its destination. */

  void receive( const Message &m );

};

# endif
