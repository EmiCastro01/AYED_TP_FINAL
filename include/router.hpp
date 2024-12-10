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

  public:
    Router(string name, int ID);
    Router();
    string get_name();
    int get_ID();
    IP get_ip();
    void process_data(Data data);   // process data, maybe we change the arguments to specify the type of processing
    void listen(Data data);     //this has to enable the router to get data from the terminal
    int flush();      // this has to send data when data is ready to be sent
    void add_neighbor(Router *router, int cost);
    void add_terminal(Terminal *terminal, int cost);
    Queue<neighbor_t> get_neighbors();
    Queue<terminals_t> get_terminals();
    

};
