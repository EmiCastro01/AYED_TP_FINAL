#include <bitset>
#include <iostream>
#include <limits>
#include <random>

#include "machines.cpp"
#include "network.cpp"
#include "simulator.cpp"
#include "structures.cpp"
#include "system_adm.cpp"
#include "utils.cpp"

using namespace std;

#define INFI std::numeric_limits<int>::max()
#define MAX_ROUTERS 256
void create_matrix(int (&adjacency_matrix)[MAX_ROUTERS][MAX_ROUTERS],
                   int routers);
Admin sys_adm;

/**
 * @brief Main program
 *
 * @return int
 */
int main() {
    configurations_t *configurations;
    configurations = load_configurations("../config.json");

    int adjacency_matrix[MAX_ROUTERS][MAX_ROUTERS];

    create_matrix(adjacency_matrix, configurations->number_of_routers);

    Network network;
    network.config(configurations);
    network.set_adjacency_matrix(adjacency_matrix);
    network.generate_network();
    sys_adm.config(configurations);
    sys_adm.set_network(&network);
    sys_adm.calculate_optimal_routes();

    Simulator simulator;
    simulator.config(&network, &sys_adm);
    simulator.debug(true);
    simulator.begin();

    return EXIT_SUCCESS;
}

/**
 * @brief Get the optimal router object
 *
 * @param __from Router startpoint (use "this")
 * @param __to Endpoint, target (ID of target Terminal)
 * @return Router*
 */

Router *get_optimal_router(Router *__from, int __to) {
    return sys_adm.get_optimal_router(__from, __to);
}

/**
 * @brief Create the Adjaency Matrix. This is used once for connections, and
 * after for congestion Map. Creates all places in matrix. After, fills with
 * random values between 1 and 3, and INFI. INFI means: no connection. -1 means:
 * no router.
 *
 * @param routers
 */
void create_matrix(int (&adjacency_matrix)[MAX_ROUTERS][MAX_ROUTERS],
                   int routers) {
    for (int i = 0; i < MAX_ROUTERS; i++) {
        for (int j = 0; j < MAX_ROUTERS; j++) {
            adjacency_matrix[i][j] = -1;
        }
    }
    for (int i = 0; i < routers; i++) {
        for (int j = 0; j < routers; j++) {
            adjacency_matrix[i][j] = rand() % 3 + 1;
            if (adjacency_matrix[i][j] == 1) {
                adjacency_matrix[i][j] = INFI;
            }
            if (i == j) adjacency_matrix[i][j] = 0;
        }
    }
}
