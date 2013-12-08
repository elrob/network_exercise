/* Filename: router.h 
   Associated implementation file: router.cpp */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 5th November 2012 */

/* This header file contains the class definition for Router
 including all the attributes and member functions. It enables
 the Router to form part of a network of Hosts and Routers through 
 which messages can be passed from Host to Host via Routers. */


#ifndef ROUTER_H
#define ROUTER_H

#include <list>
#include <map>
#include "message.h"
#include "host.h"

class Host;
class Message;

class Router {
 private:
  
  int address;
  list< Host* > connected_hosts; 
  list< Router* > neighbours;
  multimap< int, list<int> > rTable; // routing table <host address, route>


 public:
  
  Router( const int a ); //constructor


  /* getAddress() returns the integer address
     of the Router object. */

  int getAddress(); 


  /* connectTo( Host& h ) connects the Router object to 
     the Host 'h' passed as a parameter. Connection is 
     only permitted if the Host is not already connected 
     to any Router. The Router updates 'rTable' (its 
     routing table) and passes the route to the new Host
     to any neighbouring Routers. These, in turn, pass the
     new route to their neighbouring routers so the whole 
     connected network is updated. A Router stops passing 
     on a route when the route already contains its own address.
     -The Host's 'Parent' pointer becomes a pointer to the Router.
     -A pointer to 'h' is added to the Router's 'connected_hosts'.
     -private Router function 'add_host_to_rTable' is called with
      the Host's address. This function calls other functions in 
      order to pass the new route to the connected network. */

  void connectTo( Host& h );

  
  /* connectTo( Router& r ) connects the calling Router to 
     the Router 'r' passed as a parameter. Connection is 
     permitted as long as it doesn't already exist. Both Routers'
     routing tables are updated and all routes are passed between
     both Routers. Any routes received by either Router are then
     passed on as explained in the 'connectTo( Host& h )'
     description.
     -Both Routers update their list of 'neighbours' to include
      a pointer to the newly connected Router.
     -Routes are passed between the Routers using the private
      Router function 'pass_all_routes_to'. This function calls 
      'receiveRoute' on the newly connected Router  which calls 
      'add_route_to_rTable' which calls 'passRoute' which again 
      calls 'receiveRoute'. This chain enables the new connection
      to be passed to the entire connected network. */

  void connectTo( Router& r );


  /* disconnect( Host& h ) removes the connection between the 
     calling Router and the Host 'h' so long as it exists. 
     -The Host's 'Parent' pointer is set to NULL.
     -Private Router function 'delete_host_entry' is called
      to delete any routes to the Host from the routing table.
      This function recurses around the entire network to delete
      routes to the Host from all the Routers' routing tables.
     -Private Router function 'remove_from_connected_hosts' is 
      also called to remove the Host's pointer from the Router's
      list of 'connected_hosts'.  */

  void disconnect(Host& h);


  /* disconnect( Router& r) removes the connection between the 
     calling Router and the Router 'r' so long as it exists.
     -Private Router function 'delete_routes_starting' is called
      on both Routers to delete all routes in their routing tables
      starting with their newly removed neighbouring Router.
     -Private Router function 'delete_neighbour' is also called
      on both Routers to remove each other's pointers from both 
      Routers' 'neighbours' list.
     -Private Router function 'tell_neighbours_to_remove' is also
      called on both Routers with the two Router addresses passed
      as parameters. This function recursively removes all routes
      from all the Routers' routing tables that included the newly
      removed connection.   */

  void disconnectFrom(Router& r);


  /* send( const Message& m ) uses the destination address attribute
     of Message 'm' to decide whether to call the private Router 
     function 'pass_to_host' or 'pass_to_next_router' to pass on 
     the Message. If the Router cannot find a route to the 
     destination in its routing table then the Message sending 
     will stop and a console output statement will inform the user
     at which Router the Message sending failed. */

  void send( const Message& m );


  /* print_rTable() outputs 'rTable' to the console output stream
     to aid testing and debugging. */

  void print_rTable( );

  /* print_neighbours() outputs 'neighbours' to the console output 
     stream to aid testing and debugging. */

  void print_neighbours( );

  /* print_connected_hosts() outputs 'connected_hosts' to the 
     console output stream to aid testing and debugging. */

  void print_connected_hosts( );


 private:
  
  /* add_host_to_rTable( ... ) creates an integer list containing 
     only the entry -1 to indicate that it is directly 
     connected to the Host. Then calls 'add_host_to_rTable' with 
     the Host's address and this list as the Route parameter. */
  
  void add_host_to_rTable( const int host_address );
  

  /* add_route_to_rTable( ... ) appends 'host_address' as a key
     and 'route' as a value in the routing table multimap 'rTable'.
     It then calls the function passRoute with 'host_address' and 
     'route' as the parameters. */
  
  void add_route_to_rTable( const int host_address, list<int> &route );

  /* passRoute( ... ) first creates a new 'prepended_route' using
     the prependRoute function with 'route' as a parameter. It
     then iterates through its list of 'neighbours' and calls 
     the 'receiveRoute' function on each of them passing
     'host_address' and 'prepended_route' as parameters. */

  void passRoute( const int host_address, list<int> &route );


  /* prependRoute( ... ) takes an integer list as a parameter
     and returns an integer list prepended with the Router's
     integer address. */

  list< int > prependRoute( list< int > &route );

  
  /* receiveRoute( ... ) first calls function 'own_address_in_route'
     to check that the received 'route' should be added to the 
     routing table. If so, it calls 'add_route_to_rTable' with 
     'host_address' and 'route' being passed as parameters. */
  
  void receiveRoute( const int host_address, list<int> &route );


  /* own_address_in_route( ... ) iterates through the integer list
   'route' and returns 'true' if any element is equal to its own 
   address. Else it returns 'false'. */

  bool own_address_in_route( list<int> &route );  

  
  /* pass_all_routes_to( Router* r) iterates through every each
     route in the routing table and calls 'receiveRoute' on Router
     'r' with each key and each route as parameters. Before passing
     each route it gets prepended with the calling Router's address
     using function 'prependRoute'. */
  
  void pass_all_routes_to( Router* r);
  
  
  /* is_connected_host( ... ) returns 'true' if the address of Host 
   'h' is found in the calling Router's 'neighbours' list. Else it
   returns 'false'.*/ 

  bool is_connected_host( Host* h);


  /* delete_host_entry( ... ) removes any entries in the routing
   table 'rTable' of the calling Router that contain the 
   'host_address' passed as a parameter. If any entries are found, 
   and thus removed, the same function is called on all 'neighbours'
   so the routes can be removed throughout the whole connected 
   network via recursion. */

  void delete_host_entry( const int host_address );


  /* remove_from_connected_hosts( ... ) first checks that Host 
   pointer 'h' is found in the list of 'connected_hosts'. It it is,
   then it is removed. */

  void remove_from_connected_hosts( Host* h);


  /* is_neighbour( ... ) iterates through 'neighbours' and returns
     'true' if Router pointer 'r' is found. Else returns 'false'. */

  bool is_neighbour( Router* r );


  /* delete_route_starting(...) iterates through 'rTable' and 
     deletes any routes that start with 'start_address'. */

  void delete_routes_starting( const int start_address );


  /* delete_neighbour(...) iterates through the 'neighbours' list
   and deletes the entry corresponding to Router pointer 'r'. */

  void delete_neighbour( Router* r );


  /* tell_neighbours_to_remove(...) calls the function 
     'remove_routes_with' on each Router in its 'neighbours' list.
     It passes 'a1' and 'a2' as parameters in each case. */

  void tell_neighbours_to_remove( const int a1, const int a2 );


  /* remove_routes_with(...) checks every route in the routing table
     for a link between address 'a1' and 'a2'. It uses function 
     'route_has_link' to do this. All qualifying routes are removed.
     If any route is removed the function recurses, calling function
     'tell_neighbours_to_remove( a1, a2 )'. */

  void remove_routes_with( const int a1, const int a2 );


  /* 'route_has_link' tests 'route' for any occurrence of 'a1' and
     'a2' beside eachother. If so, it returns 'true', else it 
     returns 'false'. */

  bool route_has_link( list<int> &route, const int a1, const int a2 );


  /* pass_to_host(...) passes the Message 'm' to the connected Host
   using the destination attribute of the Message, matching the 
   address to one of its 'connected_hosts' and then calling Host 
   member function 'receive( m )' on that Host object. */
  
  void pass_to_host( const Message &m );


  /* pass_to_next_router(...) searches Routers in the 'neighbours' 
     list for the one that corresponds to the forward address. It 
     then calls the 'send' function on the neighbouring Router
     passing the Message 'm' as a paramter. */

  void pass_to_next_router( const Message &m, const int forward_address );

};


#endif
