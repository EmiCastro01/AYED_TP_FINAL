#include "../include/system_adm.hpp"

Admin::Admin() {
    cout << "System Administrator generated" << endl;
    cout << "No network loaded [[" << " ADMIN ]]" << endl;
}

/**
 * @brief Configures the system administrator with the configurations.
 * This is used to set the configurations by reading the config.json file.
 * Just uses the number of routers.
 * @param config
 */
void Admin::config(configurations_t *config) { this->configurations = config; }

void Admin::set_network(Network *n) { this->network = n; }

/**
 * @brief Calculate the next optimal router to reach the target (__to).
 * Uses next_hop function to get the next router (opt_fw.hpp file)
 *
 * @param __from
 * @param __to
 * @return Router*
 */
Router *Admin::get_optimal_router(Router *__from, int __to) {
    Terminal *reach_t = this->network->get_terminal_by_id(__to);
    Router *reach_r = reach_t->get_router();
    __to = reach_r->get_ID();
    cout << "Getting optimal router" << endl;
    dijkstra(this->network->get_adjacency_matrix(), __from->get_ID(), __to,
             this->network->Pre, this->configurations->number_of_routers);

    int next = next_opt(this->network->Pre, __from->get_ID(), __to);
    cout << "Next hop is: " << next << endl;
    Router *return_router = this->network->get_router_by_id(next);
    return return_router;
}

/**
 * @brief Uses Dijkstra algorithm to calculate the optimal routes.
 * (Dijkstra.hpp file)
 */

void Admin::calculate_optimal_routes() {
    cout << "Calculating optimal routes [[ ADMIN ]]" << endl;
    this->network->update_adj_with_congestion();
    /*warshall(this->network->get_adjacency_matrix(), this->network->caminos,
             this->configurations->number_of_routers);
    floyd(this->network->get_adjacency_matrix(), this->network->A,
          this->network->cf, this->configurations->number_of_routers);
          */
}

int Admin::get_current_routers_no() {
    return this->configurations->number_of_routers;
}