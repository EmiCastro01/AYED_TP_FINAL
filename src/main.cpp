#include <iostream>
#include <bitset>
#include "../include/queue.hpp"
#include "../include/tree.hpp"
#include "../include/network.hpp"
using namespace std;


int main ()
{
  
  Network network;
  network.set_adjacency_matrix(
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
  cout << network.get_router_by_id(7)->get_neighbor().cost << endl; // revisar esto porque anda mal
  return EXIT_SUCCESS;
}

