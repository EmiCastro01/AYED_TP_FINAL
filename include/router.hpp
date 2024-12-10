#pragma once
#include <iostream>
#include "data.hpp"
#include "queue.hpp"

using namespace std;

typedef enum {
  OPEN,
  CLOSE,
  FLUSHING,
  NO_ASSIGNED,
} RouterGate;

typedef struct {
  int ID;
  int cost;
} neighbor_t;

class Router {
  private:
    string name;
    int ID;
    RouterGate gate;
    Queue<neighbor_t> neighbors;

  public:
    Router(string name, int ID);
    string get_name();
    int get_ID();
    void process_data(Data data);   // process data, maybe we change the arguments to specify the type of processing
    void listen(Data data);     //this has to enable the router to get data from the terminal
    int flush();      // this has to send data when data is ready to be sent
};

Router::Router(string name, int ID) {
  this->name = name;
  this->ID = ID;
  this->gate = NO_ASSIGNED;
}

string Router::get_name() {
  return this->name;
}

int Router::get_ID() {
  return this->ID;
}

void Router::process_data(Data data) {
  cout << "Processing data" << endl;
  this->gate = CLOSE;
}

void Router::listen(Data data) {
  cout << "Listening to data" << endl;
  this->gate = OPEN;
}

int Router::flush() {
  this->gate = FLUSHING;
  cout << "Flushing data" << endl;
  this->gate = CLOSE;
  return 0;
}

