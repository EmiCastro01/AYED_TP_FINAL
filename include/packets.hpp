#pragma once
#include <iostream>
#include "queue.hpp"

using namespace std;

typedef int IP;
typedef struct {
  string data;
} Data;

typedef struct {
  Data data;
  IP destination;
  bool last_package; // if the packet is the last packet of the page
} Packet;

typedef struct {
  int number_of_packets;
  Queue<Packet> packets;
} Page;

