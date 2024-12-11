#include <iostream>

using namespace std;

/**
 * @brief Simulator can execute cycles of the network, simulating the behavior
 * of sending and receiving data, and the state of the network.
 * 
 * Can be set to debug mode to run a cycle and print the state of the network
 * 
 */
class Simulator {
  public:
    Simulator();
    void begin();
    void debug(bool debug_mode);
    void cycle();
  private:
    bool debug_mode;    
};

Simulator::Simulator() {
  this->debug_mode = false;
}

void Simulator::debug(bool debug_mode) {
  this->debug_mode = debug_mode;
}
void Simulator::begin() {
  cout << "Simulation initialized!!" << endl;
  if(this->debug_mode) {
    cout << "Running on Debug mode" << endl;
    while (true) {
    
    
    cycle();

    cout << "Press any key to next cycle" << endl;
    cin.get();
    }
  }
  }

void Simulator::cycle() {
  
}
  
