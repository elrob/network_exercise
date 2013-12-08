/* Filename: router.cpp 
   Associated header file: router.h */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 5th November 2012 */

/* This implementation file contains all function definitions
   for the Router class defined in header file 'router.h'. */


#include <iostream>

using namespace std;

#include "router.h"

/* BEGIN CONSTRUCTOR DEFINITON */
Router::Router( const int a ) {
  address = a;
}
/* END CONSTRUCTOR DEFINITION */


/* BEGIN FUNCTION DEFINITION */
int Router::getAddress() {
  return address;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::connectTo( Host& h ) {
  if ( h.getParent() == NULL ) //check for unconnected host 
    {
      h.setParent(this);
      connected_hosts.push_back(&h); 
      add_host_to_rTable( h.getAddress() ); 
    }
  else
    cout << "Unable to connect Host " << h.getAddress()
	 << " to Router " << address << ". Host "
	 << h.getAddress() << " is " 
	 << ((h.getParent()->getAddress()==address)?"already ":"")
	 << "connected to Router " << h.getParent()->getAddress()
	 << ".\n" << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::connectTo( Router& r ) {
  //check they aren't already connected
  if ( ! is_neighbour(  &r ) && &r != this )
    {
      neighbours.push_back( &r );
      r.neighbours.push_back( this );
      pass_all_routes_to( &r );
      r.pass_all_routes_to( this );
    }
  else
    cout << "Router with address: " << r.getAddress()
	 << " is already connected to Router: " << this->address 
	 << endl << endl;
      
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::disconnect( Host& h) {
  // check that they are connected
  if ( is_connected_host( &h ) )
    {
      h.setParent( NULL );
      delete_host_entry( h.getAddress() );
      remove_from_connected_hosts( &h );
    }
  else
    cout << "Host " << h.getAddress() << " is not directly connected to Router " << address << " so this disconnection is forbidden!\n" << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::disconnectFrom( Router &r) {
  if ( is_neighbour( &r ) )  //check that they are neighbours!!
    {
      delete_routes_starting( r.getAddress() );
      r.delete_routes_starting( address );
      //delete each other from neighbours list
      delete_neighbour( &r );
      r.delete_neighbour( this );
      // tell neighbours about lost connection
      tell_neighbours_to_remove( address, r.getAddress() );
      r.tell_neighbours_to_remove( address, r.getAddress() );
    }
  else
    cout << "Router " << address << " and Router " << r.getAddress()
	 << " are not directly connected so this disconnection is forbidden!\n" << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::send( const Message &m ) { 
  multimap< int, list<int> >::iterator it;
  it = rTable.find( m.getDestination() );
  if ( it != rTable.end( ) )
    {
      int forward_address = *((*it).second.begin());
      if ( forward_address == -1 )
	pass_to_host( m );
      else
	pass_to_next_router( m, forward_address );
    }
  else
    cout << "Routing of message failed at Router " << address << "." << endl << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::print_rTable( ) {
  cout << "rTable for router address: " << address << endl;
  multimap< int, list<int> >::iterator it;
  for ( it=rTable.begin() ; it != rTable.end(); it++ )
    {
      cout << (*it).first << " => ";
      list< int >::iterator list_it;
      for ( list_it = (*it).second.begin() ; list_it != (*it).second.end(); list_it++ )
	{
	  cout << *list_it << " ";
	}
      cout << endl;
    }
  cout << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::print_neighbours( ) {
  cout << "neighbours for router address: " << address << endl;
  list< Router* >::iterator it;
  for ( it = neighbours.begin() ; it != neighbours.end(); it++ )
    {
      cout << *it << " " << (*it)->getAddress() << endl;
    }
  cout << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::print_connected_hosts( ) {
  cout << "connected hosts for router address: " << address << endl;
  list< Host* >::iterator it;
  for ( it = connected_hosts.begin() ; it != connected_hosts.end(); it++ )
    {
      cout << *it << " " << (*it)->getAddress() << endl;
    }
  cout << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::add_host_to_rTable( const int host_address ) {
  list<int> route;
  // -1 used to indicate end of route (host-router connection)
  route.push_back( -1 );
  add_route_to_rTable( host_address, route );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::add_route_to_rTable( const int host_address, list<int> &route ) {
  rTable.insert( pair< int, list<int> >( host_address, route ) );
  passRoute( host_address, route );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::passRoute( const int host_address, list<int> &route ) {
  list<int> prepended_route = prependRoute( route );
  for ( list< Router* >::iterator it = neighbours.begin(); it != neighbours.end(); it++ )
    (*(*it)).receiveRoute( host_address, prepended_route );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
list< int > Router::prependRoute( list<int> &route ) {
  list< int > prepended_route = route;
  prepended_route.push_front( address );
  return prepended_route;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::receiveRoute( const int host_address, list<int> &route ) {
  if ( ! own_address_in_route( route ) ) 
    add_route_to_rTable( host_address, route );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
bool Router::own_address_in_route( list<int> &route ) {
  list<int>::iterator it;
  for ( it = route.begin(); it != route.end(); it++ )
    if ( *it == address )
      return true;
  
  return false;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::pass_all_routes_to( Router* r ) {
   multimap< int, list<int> >::iterator it;
   for ( it = rTable.begin() ; it != rTable.end(); it++ )
     {
       list< int > prepended_route = prependRoute( (*it).second ) ;
       r->receiveRoute( (*it).first, prepended_route );
     }
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
bool Router::is_connected_host( Host* h ) {
  list< Host* >::iterator it;
  it = connected_hosts.begin();
  while ( it != connected_hosts.end() && *it != h )
    it++;
  if ( it != connected_hosts.end() )
    return true;
  else 
    return false;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::delete_host_entry( const int host_address ) {
  multimap< int, list<int> >::iterator it;
  bool host_found = false;
  it = rTable.find( host_address );
  while ( it != rTable.end() )
    {
      host_found = true;
      rTable.erase( it );
      it = rTable.find( host_address );
    }
  if ( host_found ) //continue recursion
    for ( list< Router* >::iterator it = neighbours.begin(); it != neighbours.end(); it++ )
      (*it)->delete_host_entry( host_address );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::remove_from_connected_hosts( Host* h ) {
  list< Host* >::iterator it;
  it = connected_hosts.begin();
  while ( it != connected_hosts.end() && *it != h )
    it++;
  if ( *it == h )
    connected_hosts.erase( it );
  else
    cout << "Host " << h->getAddress() << " is not directly connected to Router " << address << " so it can't be removed from connected hosts!" << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
bool Router::is_neighbour( Router* r ) {
  list< Router* >::iterator it;
  for ( it = neighbours.begin(); it != neighbours.end(); it++ )
    if ( *it == r )
      return true;
  
  return false;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::delete_routes_starting( const int start_address ) {
  multimap< int, list<int> >::iterator it;
  it = rTable.begin();
  while ( it != rTable.end() )
    if ( *((*it).second.begin()) == start_address )
      rTable.erase(it++);
    else
      it++;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::delete_neighbour( Router* r ) {
  list< Router* >::iterator it;
  it = neighbours.begin();
  while ( it != neighbours.end() && *it != r )
    it++;
  if ( *it == r )
    neighbours.erase( it );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::tell_neighbours_to_remove( const int a1, const int a2 ) {
  for ( list< Router* >::iterator it = neighbours.begin(); it != neighbours.end(); it++ )
    (*it)->remove_routes_with( a1, a2 );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::remove_routes_with( const int a1, const int a2 ) {
  bool removed_a_route = false;
  multimap< int, list<int> >::iterator it;
  for (  it = rTable.begin(); it != rTable.end(); it++ )
    if ( route_has_link( (*it).second, a1, a2 ) )
      {
	removed_a_route = true;
	rTable.erase(it);
      }
  if ( removed_a_route ) //continue recursion
    tell_neighbours_to_remove( a1, a2 );
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
bool Router::route_has_link( list<int> &route, const int a1, const int a2 ) {
  list< int >::iterator it1;
  list< int >::iterator it2;
  it1 = route.begin();
  it2 = route.begin();
  it2++;
  while ( it2 != route.end() )
    {
      if ( (*it1 == a1 && *it2 == a2) || (*it1 == a2 && *it2 == a1) )
	return true;
      it1++;
      it2++;
    }
  return false;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::pass_to_host( const Message &m ) {
  list< Host* >::iterator it;
  it = connected_hosts.begin();
  while ( (*it)->getAddress() != m.getDestination() && it != connected_hosts.end() )
	    it++;
  if ( it != connected_hosts.end() )
    (*it)->receive( m );
  else
    cout << "Host " << m.getDestination() << " not found in Router " << address << "'s list of connected hosts!" << endl << endl;
}
/* END FUNCTION DEFINITION */


/* BEGIN FUNCTION DEFINITION */
void Router::pass_to_next_router( const Message &m, const int forward_address ) {
  list< Router* >::iterator it;
  it = neighbours.begin();
  while ( it != neighbours.end() && (*it)->getAddress() != forward_address )
    it++;
  if ( it != neighbours.end() )
    (*it)->send( m );
  else
    cout << "Error: Can't find router " << forward_address << "in " << address << "'s neighbours list!" << endl;
}
/* END FUNCTION DEFINITION */




    





      
  





  







