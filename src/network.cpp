#include <iostream>
#include "../include/network.hpp"

using namespace std;

int terminals_per_router = 1;

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

  cout << "Creating routers [[ROUTERS]]..." << endl;
  for(int i = 0; i < ROUTER_MAX_NO; i++){
    Router router("Router" + to_string(i), i);
    this->routers_array[i] = router;
    cout << "Router created: " << router.get_name() << endl;
  }
  cout << "Routers are well gereated <<" << endl;
  cout << "Generating connections [[ROUTERS]]..." << endl;
  for (int i = 0; i < ROUTER_MAX_NO; i++) {
    for (int j = 0; j < ROUTER_MAX_NO; j++) {
      if (this->adjacency_matrix[i][j] != 0) {
        get_router_by_id(i)->add_neighbor(get_router_by_id(j), this->adjacency_matrix[i][j]);
        cout << "Router " << i << " connected to Router " << j <<   " with cost: " << this->adjacency_matrix[i][j] << endl;
      }
    }
  }
  cout << "Connections are well generated <<" << endl;
  cout << "Creating terminals [[TERMINALS]]..." << endl;
  int terminal_id = 0;
  for(int i = 0; i < ROUTER_MAX_NO; i++){
    for(int j = 0; j < terminals_per_router; j++){ // maybe we could change this logic, not neccessary a client for each reciever
      Terminal *terminal_r = new Terminal("Terminal" + to_string(terminal_id), RECIEVER, terminal_id);
      terminal_id++;
      Terminal *terminal_c = new Terminal("Terminal" + to_string(terminal_id), CLIENT, terminal_id);
      terminal_id++;
      get_router_by_id(i)->add_terminal(terminal_r, 1);
      get_router_by_id(i)->add_terminal(terminal_c, 1);
      cout << "Terminal created: " << terminal_c->get_name() << " is: " << terminal_c->get_type() << endl;
      cout << "Terminal created: " << terminal_r->get_name() << " is: " << terminal_r->get_type() << endl;
    }
  }
  cout << "Printing terminals per router [[NETWORK]]" << endl;
  for(int i = 0; i < ROUTER_MAX_NO; i++){
    cout << "Router " << i << " has " << get_router_by_id(i)->get_terminals().get_head().terminal->get_ID() << ", " << 
    get_router_by_id(i)->get_terminals().get_last().terminal->get_ID() << endl;
  }
  cout << "Terminals are well created <<" << endl;
  cout << "Terminals and Routers are well connected <<" << endl;
  cout << "Network is well generated [[NETWORK]]" << endl;
  
  return true;
}


Router* Network::get_router_by_id(int id) {     
  if(id < ROUTER_MAX_NO){
    return &this->routers_array[id];
  }
  return nullptr;
}

Terminal* Network::get_terminal_by_id(int id) {
  terminals_t t;
  for(int i = 0; i < ROUTER_MAX_NO; i++){
    t = this->routers_array[i].get_terminals().search(id);
    if(t.terminal != nullptr){
      if(t.terminal->get_ID() == id){
        return t.terminal;
      }
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

void Network::send_page(Page page, Terminal *terminal, IP destination) {
  cout << "Sending page to " << destination << "..." << endl;
  Packet packet;
 // TODO: Implement the send_page method
  cout << "Page sent to " << destination << "..." << endl;
}

