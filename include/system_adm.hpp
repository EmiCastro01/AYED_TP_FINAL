#pragma once
#include <iostream>

#include "dijkstra.hpp"
#include "network.hpp"
#include "utils.hpp"

using namespace std;

class Admin {
   private:
    Network *network;
    configurations_t *configurations;

   public:
    Admin();
    void config(configurations_t *config);
    void set_network(Network *network);
    Router *get_optimal_router(Router *__from, int __to);
    void calculate_optimal_routes();
    int get_current_routers_no();
};

Router *get_optimal_router(Router *__from, int __to);
