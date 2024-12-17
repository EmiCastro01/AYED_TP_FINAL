#pragma once
#include <iostream>
#include "network.hpp"
#include "opt_fw.hpp"



using namespace std;

class Admin{
  private: 
    Network *network;
  public:
    Admin();
    void load_configurations();
    void set_network(Network *network);
    Router* get_optimal_router(Router *__from, int __to);
    void calculate_optimal_routes();
    void check_congestion();
};

Router* get_optimal_router(Router *__from, int __to);
