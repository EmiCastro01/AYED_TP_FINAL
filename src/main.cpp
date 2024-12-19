#include <iostream>
#include <bitset>
#include <limits>
#include <random>

#include "network.cpp"
#include "structures.cpp"
#include "machines.cpp"
#include "system_adm.cpp"
#include "utils.cpp"
#include "simulator.cpp"

using namespace std;

#define INFI std::numeric_limits<int>::max()
#define MAX_ROUTERS 256 // a byte (IP)
void create_matrix(int (&adjacency_matrix)[MAX_ROUTERS][MAX_ROUTERS], int routers);
Admin sys_adm;
int main ()
{
  configurations_t *configurations;
  int adjacency_matrix[MAX_ROUTERS][MAX_ROUTERS];
  configurations = load_configurations("../config.json");
  create_matrix(adjacency_matrix, configurations->number_of_routers);

  Network network;
  network.config(configurations);
  network.set_adjacency_matrix( 
    adjacency_matrix
  );
  network.generate_network();
  sys_adm.config(configurations);
  sys_adm.set_network(&network);

  //network.print_adjacency_matrix();
  sys_adm.calculate_optimal_routes();

  Simulator simulator;
  simulator.config(&network, &sys_adm);
  simulator.debug(true);
  simulator.begin();


  return EXIT_SUCCESS; 
}


Router* get_optimal_router(Router *__from, int __to) {
  return sys_adm.get_optimal_router(__from, __to);
}


void create_matrix(int (&adjacency_matrix)[MAX_ROUTERS][MAX_ROUTERS], int routers) {
    for(int i = 0; i < MAX_ROUTERS; i++) {
    for(int j = 0; j < MAX_ROUTERS; j++) {
      adjacency_matrix[i][j] = -1;
    }
  }
  for(int i = 0; i < routers; i++) {
    for(int j = 0; j < routers; j++) {
     
        
      
      adjacency_matrix[i][j] = rand() % 3 + 1;
      if(adjacency_matrix[i][j] == 1) {
        adjacency_matrix[i][j] = INFI;
      }
       if(i == j)
        adjacency_matrix[i][j] = 0;
    }
  }



}
