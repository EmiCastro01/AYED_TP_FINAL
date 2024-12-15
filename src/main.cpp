#include <iostream>
#include <bitset>

#include "network.cpp"
#include "structures.cpp"
#include "machines.cpp"
#include "system_adm.cpp"
#include "utils.cpp"
#include "simulator.cpp"
using namespace std;

Admin sys_adm;
int main ()
{
  load_configurations();
  Network network;
  network.set_adjacency_matrix( //example
    {
      {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 3, 0, 0, 0, 0, 0, 0, 0},
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
  sys_adm.set_network(&network);
  Simulator simulator;
  simulator.debug(true);
  //simulator.begin();
Page p;
p.data = "Hello World, to Emi";
p.destination = 5;
p.ID = 1;

network.get_router_by_id(1)->get_entry_pages()->push(p);
network.get_router_by_id(1)->run();
network.get_router_by_id(1)->run();

network.get_router_by_id(2)->run();
network.get_router_by_id(2)->run();

network.get_router_by_id(2)->run();
network.get_router_by_id(2)->run();

network.get_router_by_id(2)->run();





  
  


  

  return EXIT_SUCCESS; 
}


Router* get_optimal_router(Router *__from, int __to) {
  cout << "Getting optimal router" << endl;
  return sys_adm.get_optimal_router(__from, __to);
}

