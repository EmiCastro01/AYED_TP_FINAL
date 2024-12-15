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
      {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
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
Page p;
p.data = "Hello World, to Emi";
p.destination = 2;
p.ID = 1;

network.get_router_by_id(0)->get_entry_pages()->push(p);
network.get_router_by_id(0)->run();
network.get_router_by_id(1)->run();



  
  


  

  return EXIT_SUCCESS; 
}


