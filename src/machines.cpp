#include <iostream>
#include "../include/router.hpp"
#include "../include/terminal.hpp"

using namespace std;


Router::Router() {
  this->name = "Router-";
  this->ID = 0;
  this->gate = NO_ASSIGNED;
}
Router::Router(string name, int ID) {
  this->name = name;
  this->ID = ID;
  this->gate = NO_ASSIGNED;
  this->ip =   MASK_ROUTER_ADDRESS & (ID <<= BYTE); // mask the ID to get the last byte
}

string Router::get_name() {
  return this->name;
}

int Router::get_ID() {
  return this->ID;
}

IP Router::get_ip() {
  return this->ip;
}

void Router::process_data(Data data) {
  cout << "Processing data" << endl;
  this->gate = CLOSE;
}

void Router::listen(Data data) {
  cout << "Listening to data" << endl;
  this->gate = OPEN;
}

int Router::flush() {
  this->gate = FLUSHING;
  cout << "Flushing data" << endl;
  this->gate = CLOSE;
  return 0;
}

void Router::add_neighbor(Router *router, int cost) {
  neighbor_t neighbor;
  neighbor.ID = router->get_ID();
  neighbor.cost = cost;
  neighbor.ip = router->get_ip();
  this->neighbors.push(neighbor);
}

void Router::add_terminal(Terminal *terminalPointer, int cost) {
  terminals_t terminal_;
  terminal_.terminal = terminalPointer;
  terminal_.terminal->connect_to_router(this);
  this->terminals.push(terminal_);
}

Queue<neighbor_t> Router::get_neighbors() {
  return this->neighbors;
}

Queue<terminals_t> Router::get_terminals() {
  return this->terminals;
}


Terminal::Terminal(string name, terminal_t type, int ID) {
  this->name = name;
  this->type = type;
  this->ID = ID;
  this->ip = MASK_TERMINAL_ADDRESS & ID; // mask the ID to get the last byte
}

void Terminal::send_data(Data data) {
  this->current_data = data;
  cout << "Sending data" << endl;
  // this->router->listen(data);  The terminal calls th router to listen to the data
}

void Terminal::receive_data(Data data) {
  this->current_data = data;
  cout << "Receiving data" << endl;
  // this->router->process_data(data);    The terminal calls the router to process the data
}

void Terminal::connect_to_router(Router *router) {
  this->router = router;
}


string Terminal::get_name() {
  return this->name;
}

Router* Terminal::get_router() {
  return this->router;
}

int Terminal::get_ID() {
  return this->ID;
}

string Terminal::get_type() {
  if (this->type == RECIEVER) {
    return "RECIEVER";
  } else {
    return "CLIENT";
  }
}
Data Terminal::get_current_data() {
  return this->current_data;
}

IP Terminal::get_ip() {
  return this->ip;
}