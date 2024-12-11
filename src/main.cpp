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
 // simulator.begin();
 Page page;
 page.data = "Hello World";
 Router r1;
 r1.listen(page);
  return EXIT_SUCCESS; 
}


