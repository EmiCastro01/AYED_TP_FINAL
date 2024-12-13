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

void Router::regenerate_pages() {
 
  // debo recorrer:
  // 1. Los vecinos
  // 2. Los paquetes con el mismo ID (misma pagina)
  // 3. Verificar si esos paquetes estan completos (esta el ultimo paquete y el tamaño de la pagina
  // IMPORTANTE: eliminar todas los punteros a colas y variables temporales al finalizar el pipeline
  // corresponde al campo size del paquete)
  // Use bubble sort to generate the page (index)

  cout << "Regenerating pages .. [[" << this->get_name() << "]]"<< endl;
  // generate a new queue with the neighbors that have packets
  Queue<neighbor_t> *neighbors_with_packets = new Queue<neighbor_t>();
  for(int i = 0; i < this->get_neighbors().size(); i++) {
    if(this->get_neighbors().search_router(i).out_packets.is_empty() == false) {
      neighbors_with_packets->push(this->get_neighbors().search_router(i));
    } 
  }
  // --------------------------------------------------- end first step --------------------
  if(neighbors_with_packets-> is_empty()){
        cout << "No pages to regenerate: No packets on neighbors queues [[ " << this->get_name() << "]]" << endl;
        delete neighbors_with_packets; 
        return;
  } else {
    // discard the queues of neighbors that not have the last packet
    Queue<neighbor_t> *neighbors_with_last_packet = new Queue<neighbor_t>();
    *neighbors_with_last_packet = *neighbors_with_packets;
    for(int i = 0; i < neighbors_with_packets->size(); i++) {
      for(int j = 0; j < neighbors_with_packets->search_router(i).out_packets.size(); j++) {
        if(neighbors_with_packets->search_router(i).out_packets.search_packet(j).last_package == true) {
          neighbors_with_last_packet->push(neighbors_with_packets->search_router(i));
          break; // no need to continue. may have more than 1 last packet
        }
      }
    }
    delete neighbors_with_packets; 
    // --------------------------------------------------- end second step --------------------
  }
  // generate 

}
void Router::listen() {
  cout << "Listening on terminals .. [[" << this->get_name() << "]]"<< endl;
  if(this->get_entry_pages()->is_empty() == true) {
    cout << "No pages on Page-Gate [[ " << this->get_name() << "]]" << endl;
  } else {
     Page *page = new Page();
  *page = this->get_entry_pages()->pop();
  generate_packets(*page); //send the content of the page to the generator
  delete page;
  cout << "Listening on Routers .. [[" << this->get_name() << "]]"<< endl;
  }
 
  if(this->get_entry_queue()->is_empty() == true) {
    cout << "No packets on Packets-Gate [[ " << this->get_name() << "]]" << endl;
  } else {
    Packet *packet = new Packet();
    *packet = this->get_entry_queue()->pop();
    cout << "Packet received: " << packet->data << ". Sending to: "<< (int)packet->destination.to_ullong() << endl;
    this->get_neighbors().search_router((int)packet->destination.to_ullong()).out_packets.push(*packet);  // Sendin just 1 packet (maybe modify)
    delete packet;
  }
}

void Router::flush() {
  cout << "Flushing ..  " << " [[" << this->get_name() << "]]"<< endl;
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
  if(this->neighbors.is_empty() == true) {
    cout << "No neighbors on Router [[ " << this->get_name() << "]]" << endl;
  }
  return this->neighbors;
}

Queue<terminals_t> Router::get_terminals() {
  if(this->terminals.is_empty() == true) {
    cout << "No terminals connected [[ " << this->get_name() << "]]" << endl;
  }
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
    packet->index = i;
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
  if(this->gate_packets.is_empty() == true) {
    cout << "No packets on Packets-Gate [[ " << this->get_name() << "]]" << endl;
  }
  return &this->gate_packets;
}

Queue<Page>* Router::get_entry_pages() {
  if(this->gate_pages.is_empty() == true) {
    cout << "No pages on Page-Gate [[ " << this->get_name() << "]]" << endl;
  }
  return &this->gate_pages;
}

void Router::run() { // CYCLE
  cout << "Running .. [[" << this->get_name() << "]]"<< endl;
  this->listen(); // 1
  this->regenerate_pages(); // 2
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