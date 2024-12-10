#pragma once
#include <iostream>
#include "router.hpp"
#include "data.hpp"
#include "terminal.hpp"

#define ROUTER_MAX_NO 10
using namespace std;

/**
 * @brief Network class is used to create a network of routers and represent
 * the connections between them.
 * Network constructor does not initialize any routers, just the object itself.
 * set_adjacency_matrix must be called to set the connections between routers.
 * generate_network must be called to create the routers due to the adjacency matrix.
 */
class Network {
  private:
    int adjacency_matrix[ROUTER_MAX_NO][ROUTER_MAX_NO];
    bool check_matrix();
    Router routers_array[ROUTER_MAX_NO];
  public:
    Network();
    void set_adjacency_matrix(const int (&matrix)[ROUTER_MAX_NO][ROUTER_MAX_NO]);
    void reinit();
    void print_adjacency_matrix();
    bool generate_network();
    Router* get_router_by_id(int id);
    Router* get_router_by_name(string name);

};

Network::Network() {
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    for (int j = 0; j < ROUTER_MAX_NO; j++) {
      this->adjacency_matrix[i][j] = 0;
    }
  }
  cout << "Network initialized with null adjancency matrix." << endl;
  cout << "No routers connected." << endl;
}

bool Network::check_matrix()
{
 for(int i = 0; i < ROUTER_MAX_NO; i++){
    if(this->adjacency_matrix[i][i] != 0){
      cout << "Error: Router " << i << " is connected to itself." << endl;
      //exit(1);
      return false;
    }
 }
  return true;
}
void Network::set_adjacency_matrix(const int (&matrix)[ROUTER_MAX_NO][ROUTER_MAX_NO]) {
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    for (int j = 0; j < ROUTER_MAX_NO; j++) {
      this->adjacency_matrix[i][j] = matrix[i][j];
    }
  }

if(check_matrix() == true){
  cout << "Adjacency matrix set." << endl;
  cout << "Network initialized with " << ROUTER_MAX_NO << " routers." << endl;
} //checks if matrix are well structured
}

void Network::reinit() {
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    for (int j = 0; j < ROUTER_MAX_NO; j++) {
      this->adjacency_matrix[i][j] = 0;
    }
  }
  cout << "Network reinitialized with null adjancency matrix." << endl;
  cout << "No routers connected." << endl;
}

void Network::print_adjacency_matrix() {
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    for (int j = 0; j < ROUTER_MAX_NO; j++) {
      cout << this->adjacency_matrix[i][j] << " ";
    }
    cout << endl;
  }
}

bool Network::generate_network() {

  for(int i = 0; i < ROUTER_MAX_NO; i++){
    Router router("Router" + to_string(i), i);
    this->routers_array[i] = router;
    cout << "Router created: " << router.get_name() << endl;
  }
  cout << "Routers are well gereated <<" << endl;
  cout << "Generating connections..." << endl;
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    for (int j = 0; j < ROUTER_MAX_NO; j++) {
      if (this->adjacency_matrix[i][j] != 0) {
        get_router_by_id(i)->add_neighbor(get_router_by_id(j), this->adjacency_matrix[i][j]);
        cout << "Router " << i << " connected to Router " << j <<   " with cost: " << this->adjacency_matrix[i][j] << endl;
      }
    }
  }
  cout << "Connections are well generated <<" << endl;
  return true;
}


Router* Network::get_router_by_id(int id) {     // We need to create another structure for this here
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    if (this->routers_array[i].get_ID() == id) {
      return &this->routers_array[i];
    }
  }
  return nullptr;
}

Router* Network::get_router_by_name(string name) {
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    if (this->routers_array[i].get_name() == name) {
      return &this->routers_array[i];
    }
  }
  return nullptr;
}