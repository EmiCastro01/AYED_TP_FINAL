#include "../include/system_adm.hpp"

Admin::Admin() {
  cout << "System Administrator generated" << endl;
  cout << "No network loaded [[" << " ADMIN ]]" << endl;
}

void Admin::set_network(Network *n) {
  this->network = n;
}

Router* Admin::get_optimal_router(Router *__from, int __to) {
  cout << "Getting optimal router" << endl;
  int next = next_hop(this->network->cf, __from->get_ID(), __to);
  cout << "Next hop is: " << next << endl;
  Router *return_router = this->network->get_router_by_id(next);
  return return_router;
}

void Admin::calculate_optimal_routes() {
  cout << "Calculating optimal routes [[ ADMIN ]]" << endl;
  this->network->update_adj_with_congestion();
  this->network->print_adjacency_matrix();
  warshall(this->network->get_adjacency_matrix(), this->network->caminos);
  floyd(this->network->get_adjacency_matrix(), this->network->A, this->network->cf);
}

