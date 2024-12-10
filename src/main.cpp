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
  cout << network.get_terminal_by_id(0)->get_router()->get_ID() << endl;
  Simulator simulator;
  simulator.debug(true);
  simulator.begin();
  return EXIT_SUCCESS; 
}


