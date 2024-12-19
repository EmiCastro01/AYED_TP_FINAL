#include <iostream>

#include "../include/router.hpp"
#include "../include/system_adm.hpp"
#include "../include/terminal.hpp"

using namespace std;

Router::Router() {
    this->name = "Router-";
    this->ID = 0;
    this->gate = NO_ASSIGNED;
}
Router::Router(string name, int ID) {
    this->gate_pages = Queue<Page>();
    this->gate_packets = Queue<Packet>();
    this->name = name;
    this->ID = ID;
    this->gate = NO_ASSIGNED;
    this->ip = MASK_ROUTER_ADDRESS &
               (ID <<= BYTE);  // mask the ID to get the last byte
    this->neighbors = Queue<neighbor_t>();
    this->terminals = Queue<terminals_t>();
}

string Router::get_name() { return this->name; }

int Router::get_ID() { return this->ID; }

IP Router::get_ip() { return this->ip; }

/**
 * @brief Third step of the run method. Obtain the optimal path to route the
 * packets to the next router, for each packet.
 *
 */
void Router::route() {
    cout << "Routing .. [[" << this->get_name() << "]]" << endl;
    for (int s = 0; s < this->get_neighbors().size(); s++) {
        if (this->get_neighbors().search_router_idx(s).out_packets.is_empty() ==
            false) {
            for (int i = 0; i < this->get_neighbors().search_router_idx(s).cost;
                 i++) {
                if (this->get_neighbors()
                        .search_router_idx(s)
                        .out_packets.is_empty() == true) {
                    break;
                }
                cout << "Routing packet to: "
                     << this->get_neighbors()
                            .search_router_idx(s)
                            .router->get_name()
                     << endl;
                this->get_neighbors()
                    .search_router_idx(s)
                    .router->get_entry_queue()
                    ->push(this->get_neighbors()
                               .search_router_idx(s)
                               .out_packets.pop());
            }
        }
    }

    cout << "Routing done [[ " << this->get_name() << "]]" << endl;
}

/**
 * @brief Second step of the run method. Regenerate the pages from the packets.
 * Gets every packets for the entry queue and checks if all packets with the
 * same ID are in the queue. If so, it regenerates the page and sends it to the
 * terminal. This process is executed just if this router is the final
 * destination (it contains the terminal).
 *
 */
void Router::regenerate_pages() {
    cout << "Regenerating pages .. [[" << this->get_name() << "]]" << endl;
    if (this->get_entry_queue()->is_empty() == true) {
        cout << "No packets on Gate [[ " << this->get_name() << "]]" << endl;
    } else {
        for (int i = 0; i < this->get_entry_queue()->size(); i++) {
            for (int j = 0;
                 j < this->get_entry_queue()->search_packet_idx(i).size; j++) {
                int ID = this->get_entry_queue()->search_packet_idx(i).ID;
                int counter_of_packets = 0;
                for (int k = 0; k < this->get_entry_queue()->size(); k++) {
                    if (this->get_entry_queue()->search_packet_idx(k).ID ==
                            ID &&
                        this->get_terminals().exists_terminal(
                            (int)this->get_entry_queue()
                                ->search_packet_idx(k)
                                .destination.to_ullong())) {
                        counter_of_packets++;
                    }
                }
                if (counter_of_packets ==
                    this->get_entry_queue()->search_packet_idx(i).size) {
                    this->get_entry_queue()->sort_packets();  // Bubble Sort
                    Page regenerating_page;
                    regenerating_page.ID = ID;
                    regenerating_page.destination = this->get_entry_queue()
                                                        ->search_packet_idx(i)
                                                        .destination;
                    for (int l = 0; l < this->get_entry_queue()->size(); l++) {
                        if (this->get_entry_queue()->search_packet_idx(l).ID ==
                            ID) {
                            regenerating_page.data += this->get_entry_queue()
                                                          ->search_packet_idx(l)
                                                          .data;
                        }
                    }
                    cout << "Page regenerated: " << regenerating_page.data
                         << ". Sending to: "
                         << (int)regenerating_page.destination.to_ullong()
                         << endl;

                    this->get_terminals()
                        .search((int)regenerating_page.destination.to_ullong())
                        .out_pages->push(regenerating_page);
                    cout << "Size of out_pages: "
                         << this->get_terminals()
                                .search((int)regenerating_page.destination
                                            .to_ullong())
                                .out_pages->size()
                         << endl;
                    for (int m = 0; m < this->get_entry_queue()->size(); m++) {
                        if (this->get_entry_queue()->search_packet_idx(m).ID ==
                            ID) {
                            this->get_entry_queue()->pop();
                        }
                    }
                }
            }
        }
    }
}
/**
 * @brief First step of the run method. Listen for packets and pages on the
 * gates. If there are pages or packets, it generates packets from the pages and
 * push the packets on the neighbors out_packets queue.
 */
void Router::listen() {
    cout << "Listening on terminals .. [[" << this->get_name() << "]]" << endl;
    if (this->get_entry_pages()->is_empty() == true) {
        cout << "No pages on Page-Gate [[ " << this->get_name() << "]]" << endl;
    } else {
        Page *page = new Page();
        *page = this->get_entry_pages()->pop();
        generate_packets(
            *page);  // send the content of the page to the generator
        delete page;
    }
    cout << "Listening on Routers .. [[" << this->get_name() << "]]" << endl;

    if (this->get_entry_queue()->is_empty() == true) {
        cout << "No packets on Packets-Gate [[" << this->get_name() << "]]"
             << endl;
    } else {
        Packet *packet = new Packet();

        for (int i = 0; i < this->get_entry_queue()->size(); i++) {
            *packet = this->get_entry_queue()->pop();
            Router *opt_router =
                get_optimal_router(this, (int)packet->destination.to_ullong());
            if (this->get_terminals().exists_terminal(
                    (int)packet->destination.to_ullong())) {
                cout << "Final destination reached " << endl;
                this->get_entry_queue()->push(*packet);
                continue;
            }
            cout << "Packet received: " << packet->data
                 << ". Destination:  " << (int)packet->destination.to_ullong()
                 << endl;
            this->get_neighbors()
                .search_neighbor(opt_router)
                .out_packets.push(*packet);
            // this->get_entry_queue()->pop();
        }
        delete packet;
    }
}

/**
 * @brief Final step of the run method. Flush the pages to the terminals.
 * If there are pages on the out_pages queue, it sends the page to the terminal.
 */
void Router::flush() {
    cout << "Flushing ..  " << " [[" << this->get_name() << "]]" << endl;
    for (int i = 0; i < this->get_terminals().size(); i++) {
        if (this->get_terminals()
                .search_terminal_idx(i)
                .out_pages->is_empty() == false) {
            cout << "Flushing page to: "
                 << this->get_terminals()
                        .search_terminal_idx(i)
                        .terminal->get_name()
                 << endl;
            this->get_terminals()
                .search_terminal_idx(i)
                .terminal->get_entry_gate()
                ->push(this->get_terminals()
                           .search_terminal_idx(i)
                           .out_pages->pop());
        }
    }
}

/**
 * @brief Add a neighbor structure (no Router object) to the neighbors queue.
 * See the neighbor_t structure in the router.hpp file.
 *
 * @param router
 * @param cost
 */
void Router::add_neighbor(Router *router, int cost) {
    neighbor_t neighbor;
    neighbor.ID = router->get_ID();
    neighbor.cost = cost;
    neighbor.ip = router->get_ip();
    neighbor.router = router;
    neighbor.out_packets = Queue<Packet>();
    neighbors.push(neighbor);
}

/**
 * @brief Add a terminal structure (no Terminal object) to the terminals queue.
 * See the terminals_t structure in the router.hpp file.
 *
 * @param terminalPointer
 * @param cost
 */
void Router::add_terminal(Terminal *terminalPointer, int cost) {
    terminals_t terminal_;
    terminal_.terminal = terminalPointer;
    terminal_.out_pages = new Queue<Page>();
    terminal_.terminal->connect_to_router(this);
    this->terminals.push(terminal_);
}

/**
 * @brief Returns a reference to the neighbors queue.
 *
 * @return Queue<neighbor_t>&
 */
Queue<neighbor_t> &Router::get_neighbors() {
    if (this->neighbors.is_empty() == true) {
        cout << "No neighbors on Router [[ " << this->get_name() << "]]"
             << endl;
    }
    return this->neighbors;
}

/**
 * @brief Returns the terminals queue.
 *
 * @return Queue<terminals_t>
 */
Queue<terminals_t> Router::get_terminals() {
    if (this->terminals.is_empty() == true) {
        cout << "No terminals connected [[ " << this->get_name() << "]]"
             << endl;
    }
    return this->terminals;
}

/**
 * @brief Takes the page on entry-gate and generates packets from it.
 * The packets are queued to the optimal router.
 * The packets are generated in a way that max size is MAX_PACKET_SIZE, and
 * amount of packets is calculated by this.
 *
 * @param page
 */
void Router::generate_packets(Page &page) {
    cout << "Generating packets.. [[" << this->get_name() << "]]" << endl;
    size_t packets_number = page.data.size() / (size_t)MAX_PACKET_SIZE;
    Packet *last_packet = new Packet();
    last_packet->data =
        page.data.substr(packets_number * MAX_PACKET_SIZE,
                         page.data.size() - packets_number * MAX_PACKET_SIZE);
    Router *opt_router =
        get_optimal_router(this, (int)page.destination.to_ullong());
    for (size_t i = 0; i < packets_number; i++) {
        Packet *packet = new Packet();
        packet->data = page.data.substr(i * MAX_PACKET_SIZE, MAX_PACKET_SIZE);
        packet->index = i;
        packet->ID = page.ID;
        packet->size = packets_number + 1;
        packet->destination = page.destination;
        packet->last_package = false;
        cout << "Packet " << i << " generated: " << packet->data
             << ". Queued to: " << opt_router->get_ID() << endl;
        this->get_neighbors()
            .search_neighbor(opt_router)
            .out_packets.push(*packet);
    }
    cout << "Last packet generated: " << last_packet->data << endl;
    last_packet->last_package = true;
    last_packet->ID = page.ID;
    last_packet->destination = page.destination;
    last_packet->size = packets_number + 1;
    last_packet->index = packets_number;
    this->get_neighbors()
        .search_neighbor(opt_router)
        .out_packets.push(*last_packet);
    cout << "All packets generated queued to neighbors.. [[" << this->get_name()
         << "]]" << endl;
}

/**
 * @brief Returns a reference to the entry queue (packets queue)
 *
 * @return Queue<Packet>*
 */
Queue<Packet> *Router::get_entry_queue() {
    if (this->gate_packets.is_empty() == true) {
        cout << "No packets on Packets-Gate [[ " << this->get_name() << "]]"
             << endl;
    }
    return &this->gate_packets;
}

/**
 * @brief Returns a reference to the entry pages queue (pages queue)
 *
 * @return Queue<Page>*
 */
Queue<Page> *Router::get_entry_pages() { return &this->gate_pages; }
/**
 * @brief Run the router. This is the main method of the router.
 *
 */
void Router::run() {  // CYCLE
    cout << "Running .. [[" << this->get_name() << "]]" << endl;
    this->listen();            // 1
    this->regenerate_pages();  // 2
    this->route();             // 3
    this->flush();             // 4
}

Terminal::Terminal(string name, terminal_t type, int ID) {
    this->name = name;
    this->type = type;
    this->ID = ID;
    this->ip = MASK_TERMINAL_ADDRESS & ID;  // mask the ID to get the last byte
    this->entry_gate = Queue<Page>();
}

/**
 * @brief Send a page to the router. The page is pushed to the entry pages
 * queue. The router has to be ran to process the page.
 *
 * @param page
 */
void Terminal::send_page(Page *page) {
    this->current_data = page->data;
    this->get_router()->get_entry_pages()->push(*page);
}

/**
 * @brief Takes the page from the entry gate and prints the data.
 *
 */
void Terminal::receive_page() {
    if (this->get_entry_gate()->is_empty() == true) {
        cout << "No pages to receive [[ " << this->get_name() << "]]" << endl;
        return;
    }
    this->current_data = this->get_entry_gate()->pop().data;
    cout << "Page received: " << this->current_data << "[[" << this->get_name()
         << "]]" << endl;
}

void Terminal::connect_to_router(Router *router) { this->router = router; }

string Terminal::get_name() { return this->name; }

Router *Terminal::get_router() { return this->router; }

int Terminal::get_ID() { return this->ID; }

string Terminal::get_type() {
    if (this->type == RECIEVER) {
        return "RECIEVER";
    } else {
        return "CLIENT";
    }
}

terminal_t Terminal::get_type_t() { return this->type; }

Data Terminal::get_current_data() { return this->current_data; }

IP Terminal::get_ip() { return this->ip; }

/**
 * @brief Returns a reference to the entry gate (pages queue)
 *
 * @return Queue<Page>*
 */
Queue<Page> *Terminal::get_entry_gate() { return &this->entry_gate; }