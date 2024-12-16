#include <iostream>
#include "../include/router.hpp"
#include "../include/terminal.hpp"
#include "../include/system_adm.hpp"

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
  cout << "Routing .. [[" << this->get_name() << "]]"<< endl;


      if(this->get_neighbors().search_router(2).out_packets.is_empty() == false) {
        for(int i = 0; i < this->get_neighbors().search_router(2).cost; i++) {
          if(this->get_neighbors().search_router(2).out_packets.is_empty() == false) {
           
            this->get_neighbors().search_router(2).router->get_entry_queue()->push(this->get_neighbors().search_router(2).out_packets.pop());
          } else {
            cout << "No packets to route to [[ " << this->get_name() << "]]" << endl;
          }
        }
      
  }

  cout << "Routing done [[ " << this->get_name() << "]]" << endl;
}

void Router::regenerate_pages() {
 


  cout << "Regenerating pages .. [[" << this->get_name() << "]]"<< endl;
  if(this->get_entry_queue()->is_empty() == true) {
    cout << "No packets on Gate [[ " << this->get_name() << "]]" << endl;
  } else {
  
    for(int i = 0; i < this->get_entry_queue()->size(); i++) {
      for(int j = 0; j < this->get_entry_queue()->search_packet_idx(i).size; j++) {
        int ID = this->get_entry_queue()->search_packet_idx(i).ID;
        int counter_of_packets = 0;
        for(int k = 0; k < this->get_entry_queue()->size(); k++) {
          if(this->get_entry_queue()->search_packet_idx(k).ID == ID && this->get_terminals().exists_terminal((int)this->get_entry_queue()->search_packet_idx(k).destination.to_ullong()) ) {
            counter_of_packets++;
          }
        }
        if(counter_of_packets == this->get_entry_queue()->search_packet_idx(i).size) {
          Page regenerating_page;
          regenerating_page.ID = ID;
          regenerating_page.destination = this->get_entry_queue()->search_packet_idx(i).destination;
          for(int l = 0; l < this->get_entry_queue()->size(); l++) {
            if(this->get_entry_queue()->search_packet_idx(l).ID == ID) {
              regenerating_page.data += this->get_entry_queue()->search_packet_idx(l).data;
            }
          }
          cout << "Page regenerated: " << regenerating_page.data << ". Sending to: "<< (int)regenerating_page.destination.to_ullong() << endl;
          this->get_terminals().search((int)regenerating_page.destination.to_ullong()).out_pages.push(regenerating_page);
          for(int m = 0; m < this->get_entry_queue()->size(); m++) {
            if(this->get_entry_queue()->search_packet_idx(m).ID == ID) {
              this->get_entry_queue()->pop();
            }
          cout << "Page well sent [[ " << this->get_name() << "]]" << endl;

        }
    }
  }
  
}

}
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
  }
   cout << "Listening on Routers .. [[" << this->get_name() << "]]"<< endl;

  if(this->get_entry_queue()->is_empty() == true) {
    cout << "No packets on Packets-Gate [[ " << this->get_name() << "]]" << endl;
  } else {
    Packet *packet = new Packet();
    *packet = this->get_entry_queue()->get_last();
    Router *opt_router = get_optimal_router(this, (int)packet->destination.to_ullong());
    if( this == opt_router){
        cout << "Final destination reached " << endl;
        return;
    }
    cout << "Packet received: " << packet->data << ". Sending to: "<< (int)packet->destination.to_ullong() << endl;
    opt_router->get_entry_queue()->push(*packet); // Just 1 packet
    delete packet;
    delete opt_router;
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
  Router *opt_router = get_optimal_router(this, (int)page.destination.to_ullong());
  for(size_t i = 0; i < packets_number; i++) {
    Packet *packet = new Packet();
    packet->data = page.data.substr(i * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
    packet->index = i;
    packet->ID = page.ID;
    packet->size = packets_number + 1;
    packet->destination = page.destination;
    packet->last_package = false;
    cout << "Packet " << i << " generated: " << packet->data << ". Queued to: "<< opt_router->get_ID() << endl;
    this->get_neighbors().search_neighbor(opt_router).out_packets.push(*packet);
  }
  cout << "Last packet generated: " << last_packet->data << endl;
  last_packet->last_package = true;
  last_packet->ID = page.ID;
  last_packet->destination = page.destination;
  last_packet->size = packets_number + 1;
  this->get_neighbors().search_neighbor(opt_router).out_packets.push(*last_packet);
  cout << "All packets generated queued to neighbors.. [[" << this->get_name() << "]]"<< endl;
}

Queue<Packet>* Router::get_entry_queue() {
  if(this->gate_packets.is_empty() == true) {
    cout << "No packets on Packets-Gate [[ " << this->get_name() << "]]" << endl;
  }
  return &this->gate_packets;
}

Queue<Page>* Router::get_entry_pages() {

  return &this->gate_pages;
}

void Router::run() { // CYCLE
  cout << "Running .. [[" << this->get_name() << "]]"<< endl;
  this->listen(); // 1
  this->regenerate_pages(); // 2
  this->route(); // 3
  this->flush(); // 4

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