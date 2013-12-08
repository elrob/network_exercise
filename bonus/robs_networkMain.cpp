/* Filename: robs_networkMain.cpp  */

/* MSc C++ Programming – Assessed Exercise No. 2 */

/* Author: Robert Speller
   Program last changed: 7th November 2012 */

/* This main file is used to test my solution to 
   the bonus section of the assessed exercise. */


#include<iostream>
using namespace std;

#include "router.h"
#include "host.h"
#include "message.h"

int main()
{

  Host h1(1);
  Host h2(2);
  Host h3(3);
  Host h4(4);
  Host h5(5);
  Host h6(6);
  
  Router r1(1);
  Router r2(2);
  Router r3(3);
  Router r4(4);
  Router r5(5);
  Router r6(6);
 
  cout << endl 
       << "-----------------------------------------\n"
       << "This program tests the network's ability \n"
       << "to send messages by the shortest routes. \n" 
       << "-----------------------------------------\n" << endl;

  cout << "6 Routers (1-6) are connected to one Host each (1-6)\n" << endl;

  r1.connectTo(h1);
  r2.connectTo(h2);
  r3.connectTo(h3);
  r4.connectTo(h4);
  r5.connectTo(h5);
  r6.connectTo(h6);
  
  cout << "Routers are connected in a linear fashion from 1 to 6 like this.\n 1--2--3--4--5--6\n" << endl;

  cout << "-------------------------------------------\n"
       << "               TEST 1                      \n"
       << "-------------------------------------------\n" << endl;

  r2.connectTo(r1);
  r3.connectTo(r2);
  r4.connectTo(r3);
  r5.connectTo(r4);
  r6.connectTo(r5);

  r1.print_rTable();
  
  h1.send(5, "This is test 1");

  cout << "-------------------------------------------\n"
       << "               TEST 2                      \n"
       << "-------------------------------------------\n" << endl;

  cout << "Router 6 is then connected directly to Router 1 to form a complete loop of 6 routers.\n" << endl;

  r6.connectTo(r1);

  r1.print_rTable();

  cout << "Now Router 1's routing table contains two routes to reach Host 5 but it will send a message via the shortest route:\n" << endl;

  h1.send(5, "This is test 2");

  cout << "-------------------------------------------\n"
       << "               TEST 3                      \n"
       << "-------------------------------------------\n" << endl;

  r1.print_rTable();

  cout << "Router 1's routing table contains two different routes to Host 4 of the same length. In this case it is not important which of the two routes it takes because each router along the route ensures that the message takes the shortest route. Therefore, in this case, it defaults to take the route which comes first in its routing table.\n" << endl;

  h1.send(4, "This is test 3");

 cout << "-------------------------------------------\n"
       << "               END OF TEST                \n"
       << "------------------------------------------\n" << endl;

  return 0;
}
