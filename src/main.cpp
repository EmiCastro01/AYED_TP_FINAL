#include <iostream>
#include <bitset>

#include "network.cpp"
#include "structures.cpp"
#include "machines.cpp"
#include "system_adm.cpp"
#include "utils.cpp"
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
  
  Router router1("Router1", 1);
  Terminal terminal1("Terminal1", CLIENT, 2);
  router1.add_terminal(&terminal1, 1);
   terminals_t t = router1.get_terminals().search(3);
   if(t.terminal == nullptr) {
     cout << "No se encontro el terminal" << endl;
   } else {
       cout << "El match es: " << t.terminal->get_ID() << endl;

   }
  return EXIT_SUCCESS; 
}


// Por el momento, estoy haciendo que las terminales y los routers se guarden en cada
// maquina con la estructura y no como punteros. Estaria bueno hacerlo con punteros

