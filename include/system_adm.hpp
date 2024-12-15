#pragma once
#include <iostream>
#include "network.hpp"



using namespace std;

class Admin{
  private: 
    Network network;
  public:
    void load_configurations();
};

Router* get_optimal_router(Router *__from, Router *__to);