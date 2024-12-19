#pragma once
#include <iostream>

#include "network.hpp"
#include "opt_fw.hpp"
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
    void check_congestion();
    int get_current_routers_no();
};

Router *get_optimal_router(Router *__from, int __to);
