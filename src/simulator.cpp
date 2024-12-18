#include <iostream>
#include "../include/network.hpp"
#include "../include/system_adm.hpp"
#include "../include/router.hpp"

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
  cout << "Simulation initialized!!" << endl << endl << endl;
  cout << ">><<>><<>><<>>><<>><<>><<>>><<>><<>><<>>><<>><<>><<>>" << endl;
  if(this->debug_mode) {
    cout << ">> SIMULATOR >> Running on Debug mode" << endl;
    while (true) {
    cycle();
    cout << ">> SIMULATOR >> Press any key to next cycle .." << endl;
    cin.get();
    }
  } 
  else {
    while (true) {
      //generate_traffic();
      
    }
  }
  

}

void Simulator::config(Network *network, Admin *sys_adm) {

  this->network = network;
  this->sys_adm = sys_adm;
}

void Simulator::cycle() {
  cout << ">> SIMULATOR >> Cycle: " << this->cycle_counter << endl;
  cout << ">> SIMULATOR >> Options: " << endl;
  cout << ">> SIMULATOR >> 0. Help" << endl;
  cout << ">> SIMULATOR >> 1. Sender Terminal" << endl;
  cout << ">> SIMULATOR >> 2. Run a void cycle" << endl;
  cout << ">> SIMULATOR >> 3. Run a void step" << endl;
  cout << ">> SIMULATOR >> 4. Print Adjacency Matrix (Congestion Map)" << endl;
  cout << ">> SIMULATOR >> 5. Print Connections" << endl;
  cout << ">> SIMULATOR >> 6. Router for Terminals" << endl;
  cout << ">> SIMULATOR >> 7. Receiver Terminal" << endl;
  cout << ">> SIMULATOR >> 8. Print Band-Width of Channels" << endl;
  cout << ">> SIMULATOR >> 9. Exit" << endl;
  int option;
  cin >> option;

  switch(option) {
    case 0: {
      system("clear");
      cout << "                       DEBUG GUIDE" << endl << endl;
      cout << "Debug Mode is used for execute cycles or steps on the traffic" << endl;
      cout << "simulator System. " << endl;
      cout << "When user press 'Choose Terminal', options for create a new Page will be" << endl;
      cout << "displayed." << endl;
      cout << "When user press 'Run a void cycle', every router, in rising order, will be " << endl;
      cout << "executed. Due to this, packets may be sent to destination in just 1 void cycle." << endl;
      cout << "When user press 'Run a void step', the user will be ask to insert a router to execute." << endl;
      cout << "'Print Congestion Map' & 'Print Connections' display maps with the current info*." << endl << endl;
      cout << "* Current info may be outdated beacuse of no-updating cycles." << endl;
      cin.get();
      cout << "Press any key to quit Help .. " << endl;
      cin.get();
      this->cycle_counter--;
      break;
    }
    case 1: {
      cout << ">> SIMULATOR >> Choose Terminal" << endl;
      cout << ">> SIMULATOR >> Choose Terminal ID: ";
      int terminal_id;
      cin >> terminal_id;
      Terminal *terminal_sender = this->network->get_terminal_by_id(terminal_id);
      if(terminal_sender == nullptr || terminal_sender->get_type_t() == RECIEVER) {
        cout << ">> SIMULATOR >> Invalid ID or Receiver Terminal" << endl;
        break;
      }
      cout << ">> SIMULATOR >> Terminal chosen: " << terminal_id << endl;
      cout << ">> SIMULATOR >> Choose destination terminal: ";
      int destination_id;
      cin >> destination_id;
      Terminal *terminal_receiver = this->network->get_terminal_by_id(destination_id);
      if(terminal_receiver == nullptr || terminal_receiver->get_type_t() == CLIENT) {
        cout << ">> SIMULATOR >> Invalid ID or Client Terminal" << endl;
        break;
      }
      cout << ">> SIMULATOR >> Destination terminal chosen: " << destination_id << endl;
      cout << ">> SIMULATOR >> Insert data for the page: ";
      string data;
      cin.ignore();
      getline(cin, data);
      Page page;
      page.data = data;
      page.destination = terminal_receiver->get_ip();
      page.ID = this->cycle_counter;
      terminal_sender->send_page(&page);
      cout << ">> SIMULATOR >> Sent!: ";
      break;
    }
    case 2: {
      cout << ">> SIMULATOR >> Running a void cycle" << endl;
      for(int i = 0; i < sys_adm->get_current_routers_no(); i++) {
        network->get_router_by_id(i)->run();
      }
      cout << ">> SIMULATOR >> All routers executed!" << endl;
      break;
    }
    case 3: {
      cout << ">> SIMULATOR >> Running a void step" << endl;
      cout << ">> SIMULATOR >> Choose Router ID: ";
      int router_id;
      cin >> router_id;
      Router *router = this->network->get_router_by_id(router_id);
      if(router == nullptr) {
        cout << ">> SIMULATOR >> Invalid Router ID" << endl;
        break;
      }
      router->run();
      break;
    }
    case 4: {
      cout << ">> SIMULATOR >> Printing Congestion Map" << endl;
      this->network->print_adjacency_matrix();
      break;
    }

    case 5: {
      cout << ">> SIMULATOR >> Printing Connections" << endl;
      for (int i = 0; i < this->network->get_routers_no(); i++) {
    for (int j = 0; j < this->network->get_routers_no(); j++) {
      if(this->network->get_adjacency_matrix()[i][j] == -1)
        continue;
      if (this->network->get_adjacency_matrix()[i][j] != INFI && i != j) {
        cout << "Router " << i << " connected to Router " << j <<   " with cost: " << this->network->get_router_by_id(i)->get_neighbors().search_router(j).cost << endl;
      
    }
   }
    }
  break;

    }

    case 6: {
        cout << ">> SIMULATOR >> Choose Terminal ID: ";
        int terminal_id;
        cin >> terminal_id;
        Terminal *terminal = this->network->get_terminal_by_id(terminal_id);
        if(terminal == nullptr) {
          cout << ">> SIMULATOR >> Invalid Terminal ID" << endl;
          break;
        }
        cout << ">> SIMULATOR >> Router for Terminal " << terminal_id << " is: " << terminal->get_router()->get_name() << endl;
      break;
    }
    case 7: {
      cout << ">> SIMULATOR >> Choose Terminal ID: ";
      int terminal_id;
      cin >> terminal_id;
      Terminal *terminal = this->network->get_terminal_by_id(terminal_id);
      if(terminal == nullptr || terminal->get_type_t() == CLIENT) {
        cout << ">> SIMULATOR >> Invalid Terminal ID or Client Terminal" << endl;
        break;
      }
      cout << ">> SIMULATOR >> Terminal chosen: " << terminal_id << endl;
      terminal->receive_page();
      break;
    }
    case 8: {
      cout << ">> SIMULATOR >> Printing Band-Width of Channels" << endl;
      bool structured = true;
      for (int i = 0; i < this->network->get_routers_no(); i++) {
          if(this->network->get_adjacency_matrix()[i][i] == -1)
            structured = false;
        for (int j = 0; j < this->network->get_routers_no(); j++) {
          if(this->network->get_adjacency_matrix()[i][j] == -1)
            continue;
          if (this->network->get_adjacency_matrix()[i][j] != INFI && i != j) {
            cout << this->network->get_router_by_id(i)->get_neighbors().search_router(j).cost << " ";
          }
          if(this->network->get_adjacency_matrix()[i][j] == INFI ) {
            cout << "- ";
          }
          if(i == j) {
            cout << "x ";
        }
        }
        if(structured)
        cout << endl;
      }
      break;
    }
    case 9: {
      exit(0);
      break;
    }
    default: {
      cout << ">> SIMULATOR >> Invalid option" << endl;
      break;
    }
  }
  if(this->cycle_counter % 2 == 0)
    this->sys_adm->calculate_optimal_routes();
  this->cycle_counter++;


  
}