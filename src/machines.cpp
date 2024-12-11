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
  this->gate_pages = Queue<Page>();
  this->gate_packets = Queue<Packet>();
  this->name = name;
  this->ID = ID;
  this->gate = NO_ASSIGNED;
  this->ip =   MASK_ROUTER_ADDRESS & (ID <<= BYTE); // mask the ID to get the last byte
  this->neighbors = Queue<neighbor_t>();
  this->terminals = Queue<terminals_t>();
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

void Router::route() {
  cout << "Processing .. [[" << this->get_name() << "]]"<< endl;
  this->gate = CLOSE;
}

void Router::listen() {
  cout << "Listening on terminals .. [[" << this->get_name() << "]]"<< endl;
  Page *page = new Page();
  *page = this->get_entry_pages()->pop();
  generate_packets(*page); //send the content of the page to the generator
  delete page;
}

void Router::flush() {
  this->gate = FLUSHING;
  cout << "Flushing ..  " << " [[" << this->get_name() << "]]"<< endl;
  this->gate = CLOSE;
}

void Router::add_neighbor(Router *router, int cost) {
  neighbor_t neighbor;
  neighbor.ID = router->get_ID();
  neighbor.cost = cost;
  neighbor.ip = router->get_ip();
  neighbor.router = router;
  neighbor.out_packets = Queue<Packet>();
  neighbors.push(neighbor);
}

void Router::add_terminal(Terminal *terminalPointer, int cost) {
  terminals_t terminal_;
  terminal_.terminal = terminalPointer;
  terminal_.terminal->connect_to_router(this);
  this->terminals.push(terminal_);
}

Queue<neighbor_t>& Router::get_neighbors() {
  return this->neighbors;
}

Queue<terminals_t> Router::get_terminals() {
  return this->terminals;
}

void Router::generate_packets(Page& page) {
  cout << "Generating packets.. [[" << this->get_name() << "]]"<< endl;
  size_t packets_number = page.data.size() / (size_t)MAX_PACKET_SIZE;
  Packet *last_packet = new Packet();
  last_packet->data = page.data.substr(packets_number * MAX_PACKET_SIZE, page.data.size() - packets_number * MAX_PACKET_SIZE);
  for(size_t i = 0; i < packets_number; i++) {
    Packet *packet = new Packet();
    packet->data = page.data.substr(i * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
    packet->destination = page.destination;
    packet->last_package = false;
    cout << "Packet " << i << " generated: " << packet->data << ". Sending to: "<< (int)page.destination.to_ullong() << endl;
    this->get_neighbors().search_router((int)page.destination.to_ullong()).out_packets.push(*packet);
  }
  cout << "Last packet generated: " << last_packet->data << endl;
  last_packet->last_package = true;
  last_packet->destination = page.destination;
  this->get_neighbors().search_router((int)page.destination.to_ullong()).out_packets.push(*last_packet);
  cout << "All packets generated and sent to neighbors.. [[" << this->get_name() << "]]"<< endl;
}

Queue<Packet>* Router::get_entry_queue() {
  return &this->gate_packets;
}

Queue<Page>* Router::get_entry_pages() {
  return &this->gate_pages;
}

void Router::run() {
  cout << "Running .. [[" << this->get_name() << "]]"<< endl;
  this->listen();
}

Terminal::Terminal(string name, terminal_t type, int ID) {
  this->name = name;
  this->type = type;
  this->ID = ID;
  this->ip = MASK_TERMINAL_ADDRESS & ID; // mask the ID to get the last byte
}


void Terminal::send_page(Page page) {
  
}

void Terminal::receive_page(Page page) {
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