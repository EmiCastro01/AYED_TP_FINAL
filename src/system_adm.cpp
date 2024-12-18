#include "../include/system_adm.hpp"

Admin::Admin() {
  cout << "System Administrator generated" << endl;
  cout << "No network loaded [[" << " ADMIN " << endl;
}

void Admin::set_network(Network *n) {
  this->network = n;
}

Router* Admin::get_optimal_router(Router *__from, int __to) {
  cout << "Getting optimal router" << endl;
  return this->network->get_router_by_id(2);
}