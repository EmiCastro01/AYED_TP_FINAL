#pragma once
#include <iostream>
#include "router.hpp"
#include "data.hpp"
using namespace std;

class Terminal {
  private: 
    Router *router;
    string name;
  public:
    Terminal(string name);  
    void send_data(Data data);
    void receive_data(Data data);
    void connect_to_router(Router *router);
    string get_name();
    Router* get_router();
};