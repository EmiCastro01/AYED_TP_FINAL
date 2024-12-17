#include <iostream>

using namespace std;

/**
 * @brief Simulator can execute cycles of the network, simulating the behavior
 * of sending and receiving data, and the state of the network.
 * 
 * Can be set to debug mode to run a cycle and print the state of the network
 * debug mode is false on default.
 * 
 * Simulator needs to be configurated with a netowrk and an administrator object.
 * 
 * Strong debug mode enable user to insert data for pages, packets, etc.
 */
class Simulator {
  public:
    Simulator();
    void begin();
    void debug(bool debug_mode);
    void config(Network *network, Admin *sys_adm);
  private:
 
    bool debug_mode;   
    int cycle_counter;
    Network *network;
    Admin *sys_adm;
    void cycle();
};

Simulator::Simulator() {
  this->debug_mode = false;
  this->cycle_counter = 0;
}

void Simulator::debug(bool debug_mode) {
  this->debug_mode = debug_mode;
}


void Simulator::begin() {
  cout << "Simulation initialized!!" << endl;
  if(this->debug_mode) {
    cout << ">> SIMULATOR >> Running on Debug mode" << endl;
    while (true) {
    cycle();
    cout << ">> SIMULATOR >> Press any key to next cycle .." << endl;
    cin.get();
    }
  }
  

}

void Simulator::config(Network *network, Admin *sys_adm) {

  this->network = network;
  this->sys_adm = sys_adm;
}

void Simulator::cycle() {
  cout << ">> SIMULATOR >> Cycle: " << this->cycle_counter << endl;
  cout << ">> SIMULATOR >> Terminal: " << cycle_counter % 10 << endl;
  cout << ">> SIMULATOR >> Send Page?: y/n" << endl;
  char c;
  cin >> c;
  if(c == 'y') {
    Page page;
    page.ID = this->cycle_counter;
    cout << ">> SIMULATOR >> Enter data for page: " << endl;
    cin >> page.data;
    page.destination = 4;
    this->network->get_terminal_by_id(cycle_counter % 10)->send_page(&page);
  }
  this->network->get_router_by_id(cycle_counter % 10)->run();
  if(cycle_counter % 2 == 0) {
    this->sys_adm->calculate_optimal_routes();    // every 2 cycles calculate optimal routes (congestion)
  }
  this->cycle_counter++;
; 
}


  
