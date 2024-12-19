#include "../include/network.hpp"

#include <iostream>
#include <random>

#define INFI std::numeric_limits<int>::max()

using namespace std;

Network::Network() {
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        for (int j = 0; j < ROUTER_MAX_NO; j++) {
            this->adjacency_matrix[i][j] = 0;
        }
    }
    cout << "Network initialized with null adjancency matrix." << endl;
    cout << "No routers connected." << endl;
}
/**
 * @brief Getter for the adjacency matrix. In runtime always returns the
 * congestion Map.
 *
 */
const int (&Network::get_adjacency_matrix()
               const)[ROUTER_MAX_NO][ROUTER_MAX_NO] {
    return this->adjacency_matrix;
}

bool Network::check_matrix() {
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        if (this->adjacency_matrix[i][i] != 0) {
            cout << "Error: Router " << i << " is connected to itself." << endl;
            // exit(1);
            return false;
        }
    }
    return true;
}
/**
 * @brief Setter for adjacency matrix. This method sets the connections between
 * routers. This is used once to set the connections.
 */
void Network::set_adjacency_matrix(
    const int (&matrix)[ROUTER_MAX_NO][ROUTER_MAX_NO]) {
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        for (int j = 0; j < ROUTER_MAX_NO; j++) {
            this->adjacency_matrix[i][j] = matrix[i][j];
        }
    }

    if (check_matrix() == true) {
        cout << "Adjacency matrix set." << endl;
        cout << "Network initialized with " << ROUTER_MAX_NO << " routers."
             << endl;
    }  // checks if matrix are well structured
}

void Network::reinit() {
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        for (int j = 0; j < ROUTER_MAX_NO; j++) {
            this->adjacency_matrix[i][j] = 0;
        }
    }
    cout << "Network reinitialized with null adjancency matrix." << endl;
    cout << "No routers connected." << endl;
}

/**
 * @brief Prints the matrix.
 *
 */
void Network::print_adjacency_matrix() {
    bool structured = true;
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        if (this->adjacency_matrix[i][i] == -1) structured = false;

        for (int j = 0; j < ROUTER_MAX_NO; j++) {
            if (this->adjacency_matrix[i][j] == -1) continue;

            if (this->adjacency_matrix[i][j] == INFI) {
                cout << "- ";
            } else if (i == j) {
                cout << "x ";
            } else {
                cout << this->adjacency_matrix[i][j] << " ";
            }
        }
        if (structured) cout << endl;
    }
}

/**
 * @brief Gets the matrix once and creates the routers, terminals, and
 * connections. The terminal type are assigned randomly.
 *
 * @return true if the network is well generated.
 * @return false jf the network is not well generated.
 */

bool Network::generate_network() {
    cout << "Creating routers [[ROUTERS]]..." << endl;
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        if (this->adjacency_matrix[i][i] == -1) break;
        Router router("Router" + to_string(i), i);
        this->routers_array[i] = router;
        cout << "Router created: " << router.get_name() << endl;
    }
    cout << "Routers are well gereated <<" << endl;
    cout << "Generating connections [[ROUTERS]]..." << endl;
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        for (int j = 0; j < ROUTER_MAX_NO; j++) {
            if (this->adjacency_matrix[i][j] == -1) continue;
            if (this->adjacency_matrix[i][j] != 0 &&
                this->adjacency_matrix[i][j] != INFI && i != j) {
                get_router_by_id(i)->add_neighbor(get_router_by_id(j),
                                                  this->adjacency_matrix[i][j]);
                if (this->adjacency_matrix[i][j] != INFI)
                    cout << "Router " << i << " connected to Router " << j
                         << " with cost: " << this->adjacency_matrix[i][j]
                         << endl;
            }
        }
    }
    cout << "Connections are well generated <<" << endl;
    cout << "Creating terminals [[TERMINALS]]..." << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    int terminal_id = 0;
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        if (this->adjacency_matrix[i][i] == -1) break;
        for (int j = 0; j < terminals_per_router; j++) {
            terminal_t type = dis(gen) == 0 ? RECIEVER : CLIENT;
            Terminal* terminal = new Terminal(
                "Terminal" + to_string(terminal_id), type, terminal_id);
            terminal_id++;
            get_router_by_id(i)->add_terminal(terminal, 1);
            cout << "Terminal created: " << terminal->get_name()
                 << " is: " << terminal->get_type() << endl;
        }
    }
    cout << "Printing terminals per router [[NETWORK]]" << endl;
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        if (this->adjacency_matrix[i][i] == -1) break;
        cout << "Router " << i << " has ";
        for (int j = 0; j < terminals_per_router; j++) {
            cout << get_router_by_id(i)
                        ->get_terminals()
                        .search_terminal_idx(j)
                        .terminal->get_name()
                 << ", ";
        }
        cout << endl;
    }
    cout << "Terminals are well created <<" << endl;
    cout << "Terminals and Routers are well connected <<" << endl;
    cout << "Network is well generated [[NETWORK]]" << endl;

    return true;
}

/**
 * @brief Search for a router by its ID. ID is a masked integer from IP.
 * The searching method is O(1) since the routers are stored in an array.
 *
 * @param id
 * @return Router*
 */
Router* Network::get_router_by_id(int id) {
    if (id < ROUTER_MAX_NO) {
        return &this->routers_array[id];
    }
    return nullptr;
}

/**
 * @brief Search for a terminal by its ID. ID is a masked integer from IP.
 * The searching method is O(n) beacuse terminals are not stored in an array,
 * but in a list. This method is only used for sending and receiving pages, so
 * is not a time consuming method.
 * @param id
 * @return Terminal*
 */
Terminal* Network::get_terminal_by_id(int id) {
    terminals_t t;
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        t = this->routers_array[i].get_terminals().search(id);
        if (t.terminal != nullptr) {
            if (t.terminal->get_ID() == id) {
                return t.terminal;
            }
        }
    }
    return nullptr;
}

/**
 * @brief Maximum number of routers in the network.
 *
 * @return int
 */

int Network::get_routers_no() { return ROUTER_MAX_NO; }

/**
 * @brief Search for a router by its name. The searching method is O(1)
 * because are stored in an array.
 *
 * @param name
 * @return Router*
 */

Router* Network::get_router_by_name(string name) {
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        if (this->routers_array[i].get_name() == name) {
            return &this->routers_array[i];
        }
    }
    return nullptr;
}

/**
 * @brief This is executed on simulation. It updates the congestion map, and
 * uses the same matrix of connections for optimization.
 *
 */
void Network::update_adj_with_congestion() {
    for (int i = 0; i < ROUTER_MAX_NO; i++) {
        for (int j = 0; j < ROUTER_MAX_NO; j++) {
            if (this->adjacency_matrix[i][j] != INFI && i != j &&
                this->adjacency_matrix[i][j] != -1) {
                this->adjacency_matrix[i][j] = this->routers_array[i]
                                                   .get_neighbors()
                                                   .search_router(j)
                                                   .out_packets.size();
            }
        }
    }
}

/**
 * @brief Configures the network. (Uses just the terminals per router
 * configuration)
 *
 * @param configurations
 */
void Network::config(configurations_t* configurations) {
    this->terminals_per_router = configurations->terminals_per_router;
}