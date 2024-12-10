#pragma once
#include <iostream>
#include "packets.hpp"

#define MASK_TERMINAL_ADDRESS 0x00FF

using namespace std;

class Router;

typedef enum {
  RECIEVER,
  CLIENT
} terminal_t;

class Terminal {
  private: 
    Router *router;
    string name;
    terminal_t type;
    Data current_data;
    int ID;
    IP ip;

  public:
    Terminal(string name, terminal_t type, int ID);  
    void send_data(Data data);
    void receive_data(Data data);
    void connect_to_router(Router *router);
    string get_name();
    int get_ID();
    IP get_ip();
    Router* get_router();
    Data get_current_data();
    string get_type();
};
