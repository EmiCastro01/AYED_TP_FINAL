#pragma once
#include <iostream>
#include "packets.hpp"
#include "queue.hpp"
#include "terminal.hpp"

#define MASK_ROUTER_ADDRESS 0xFF00

using namespace std;

typedef enum {
  OPEN,
  CLOSE,
  FLUSHING,
  NO_ASSIGNED,
} RouterGate;

typedef struct {
  int ID;
  int cost;
  IP ip;
  Router *router;
  Queue<Packet> out_packets;
} neighbor_t;

typedef struct {
  Terminal* terminal;
  Queue<Data> data;
} terminals_t;

class Router {
  private:
    string name;
    int ID;
    IP ip;
    RouterGate gate;
    Queue<neighbor_t> neighbors;
    Queue<terminals_t> terminals;
    Queue<Packet> gate_packets; // entry data from other routers
    Queue<Page> gate_pages;     // entry data from terminals
    void generate_packets(Page& page);

  public:
    Router(string name, int ID);
    Router();
    string get_name();
    int get_ID();
    IP get_ip();
    void route();   // Execute the process of redirect packets
    void listen();  
    void flush();      // send the page to local terminal
    void add_neighbor(Router *router, int cost);
    void add_terminal(Terminal *terminal, int cost);
    Queue<neighbor_t> get_neighbors();
    Queue<terminals_t> get_terminals();
    Queue<Packet>* get_entry_queue();
    Queue<Page>* get_entry_pages();
    void run();
};
