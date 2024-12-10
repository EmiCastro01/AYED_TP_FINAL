#pragma once
#include <iostream>
#include "router.hpp"
#include "data.hpp"
#include "terminal.hpp"

#define ROUTER_MAX_NO 10
using namespace std;

class Network {
  private:
    int adjacency_matrix[ROUTER_MAX_NO][ROUTER_MAX_NO];
    bool check_matrix();
  public:
    Network();
    void set_adjacency_matrix(const int (&matrix)[ROUTER_MAX_NO][ROUTER_MAX_NO]);
    void reinit();
    void print_adjacency_matrix();
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