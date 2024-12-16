#pragma once
#include <iostream>
#include "network.hpp"



using namespace std;

class Admin{
  private: 
    Network *network;
  public:
    Admin();
    void load_configurations();
    void set_network(Network *network);
    Router* get_optimal_router(Router *__from, int __to);
};

Router* get_optimal_router(Router *__from, int __to);
