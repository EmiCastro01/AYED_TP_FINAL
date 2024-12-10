#pragma once
#include <iostream>
#include "router.hpp"
#include "data.hpp"
using namespace std;

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
  public:
    Terminal(string name, terminal_t type);  
    void send_data(Data data);
    void receive_data(Data data);
    void connect_to_router(Router *router);
    string get_name();
    Router* get_router();
    Data get_current_data();
};

Terminal::Terminal(string name, terminal_t type) {
  this->name = name;
  this->type = type;
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

Data Terminal::get_current_data() {
  return this->current_data;
}
