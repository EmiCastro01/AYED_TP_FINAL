#pragma once
#include <iostream>
#include "router.hpp"
#include "packets.hpp"
#include "terminal.hpp"

#define ROUTER_MAX_NO 10
using namespace std;

/**
 * @brief Network class is used to create a network of routers and represent
 * the connections between them.
 * Network constructor does not initialize any routers, just the object itself.
 * set_adjacency_matrix must be called to set the connections between routers.
 * generate_network must be called to create the routers due to the adjacency matrix.
 * 
 * To get the list of routers, use the routers_array because every router has a unique ID then
 * it is not heavy to get the router by its ID.
 */
class Network {
  private:
    int adjacency_matrix[ROUTER_MAX_NO][ROUTER_MAX_NO];
    bool check_matrix();
    Router routers_array[ROUTER_MAX_NO];
  public:
    Network();
    void set_adjacency_matrix(const int (&matrix)[ROUTER_MAX_NO][ROUTER_MAX_NO]);
    void reinit();
    void print_adjacency_matrix();
    bool generate_network();
    Router* get_router_by_id(int id);
    Router* get_router_by_name(string name);

};
