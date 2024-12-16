#include <iostream>
#include <bitset>
#include <limits>

#include "network.cpp"
#include "structures.cpp"
#include "machines.cpp"
#include "system_adm.cpp"
#include "utils.cpp"
#include "simulator.cpp"

using namespace std;

#define INFI std::numeric_limits<int>::max()

Admin sys_adm;
int main ()
{
  load_configurations();
  Network network;
  network.set_adjacency_matrix( //example
    {
      {0, 3, INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI},
      {1, 0, 3, INFI, INFI, INFI, INFI, INFI, INFI, INFI},
      {INFI, 1, 0, 1, INFI, INFI, INFI, INFI, INFI, INFI},
      {INFI, INFI, 1, 0, 1, INFI, INFI, INFI, INFI, INFI},
      {INFI, INFI, INFI, 1, 0, 1, INFI, INFI, INFI, INFI},
      {INFI, INFI, INFI, INFI, 1, 0, 1, INFI, INFI, INFI},
      {INFI, INFI, INFI, INFI, INFI, 1, 0, 1, INFI, INFI},
      {INFI, INFI, INFI, INFI, INFI, INFI, 1, 0, 1, INFI},
      {INFI, INFI, INFI, INFI, INFI, INFI, INFI, 1, 0, 1},
      {INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, 1, 0}
    }
  );
  network.generate_network();
  sys_adm.set_network(&network);
  sys_adm.calculate_optimal_routes();

  Simulator simulator;
  simulator.debug(true);
  //simulator.begin();
Page p;
p.data = "Hello World, to Emi";
p.destination = 4;
p.ID = 1;

Page p2;
p2.data = "Hello World, to terminal 0";
p2.destination = 0;
p2.ID = 2;

network.get_router_by_id(1)->get_entry_pages()->push(p);
network.get_router_by_id(2)->get_entry_pages()->push(p2);
network.get_router_by_id(1)->run();
network.get_router_by_id(2)->run();
network.get_router_by_id(1)->run();





  

  return EXIT_SUCCESS; 
}


Router* get_optimal_router(Router *__from, int __to) {
  cout << "Getting optimal router" << endl;
  return sys_adm.get_optimal_router(__from, __to);
}