#pragma once
#include <iostream>

#include "packets.hpp"
#include "router.hpp"
#include "terminal.hpp"
#include "utils.hpp"

#define ROUTER_MAX_NO 256
using namespace std;

/**
 * @brief Network class is used to create a network of routers and represent
 * the connections between them.
 * Network constructor does not initialize any routers, just the object itself.
 * set_adjacency_matrix must be called to set the connections between routers.
 * generate_network must be called to create the routers due to the adjacency
 * matrix.
 *
 * Network can be configured using the config method. This is used to set
 * configurations by reading the config.json file (on main.cpp).
 */
class Network {
   private:
    int adjacency_matrix[ROUTER_MAX_NO][ROUTER_MAX_NO];
    /**
     * Check if the adjacency matrix is correct.
     */
    bool check_matrix();
    Router routers_array[ROUTER_MAX_NO];
    int terminals_per_router;

   public:
    int Pre[ROUTER_MAX_NO];
    int A[ROUTER_MAX_NO][ROUTER_MAX_NO];
    int cf[ROUTER_MAX_NO][ROUTER_MAX_NO];
    Network();
    void config(configurations_t* configurations);
    void set_adjacency_matrix(
        const int (&matrix)[ROUTER_MAX_NO][ROUTER_MAX_NO]);
    void update_adj_with_congestion();
    void reinit();
    void print_adjacency_matrix();
    bool generate_network();
    int get_routers_no();
    Router* get_router_by_id(int id);
    Router* get_router_by_name(string name);
    Router* get_router_by_ip(IP ip);
    Terminal* get_terminal_by_id(int id);
    Terminal* get_terminal_by_name(string name);
    Terminal* get_terminal_by_ip(IP ip);
    const int (&get_adjacency_matrix() const)[ROUTER_MAX_NO][ROUTER_MAX_NO];
};
