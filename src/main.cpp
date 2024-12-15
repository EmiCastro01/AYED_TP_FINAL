#include <iostream>
#include <bitset>

#include "network.cpp"
#include "structures.cpp"
#include "machines.cpp"
#include "system_adm.cpp"
#include "utils.cpp"
#include "simulator.cpp"
using namespace std;


int main ()
{
  load_configurations();
  Network network;
  network.set_adjacency_matrix( //example
    {
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    }
  );

  network.generate_network();
  Simulator simulator;
  simulator.debug(true);
  //simulator.begin();
  Packet p = Packet();
  p.data = "Hello";
  p.destination = 2;
  p.ID = 1;
  p.index = 0;
  p.last_package = false;
  p.size = 3;
  Packet p2 = Packet();
  p2.data = " World";
  p2.destination = 2;
  p2.ID = 1;
  p2.index = 1;
  p2.last_package = false;
  p2.size = 3;
  Packet p3 = Packet();
  p3.data = ". Emi";
  p3.destination = 2;
  p3.ID = 1;
  p3.index = 2;
  p3.last_package = true;
  p3.size = 3;


  
  network.get_router_by_id(1)->get_entry_queue()->push(p);
  network.get_router_by_id(1)->get_entry_queue()->push(p2);
  network.get_router_by_id(1)->get_entry_queue()->push(p3);
  network.get_router_by_id(1)->run();
  network.get_router_by_id(1)->run();
    network.get_router_by_id(1)->run();



  

  return EXIT_SUCCESS; 
}


