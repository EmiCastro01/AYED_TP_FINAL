#pragma once
#include <iostream>
#include <bitset>
#include "queue.hpp"

#define BYTES_PER_IP 2
#define BYTE 8
using namespace std;

typedef bitset<BYTES_PER_IP * BYTE> IP;

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


// TODO: Every packet has a destination IP, so 
// router recieves a packet and checks where to send it
// when the destination router (first byte of IP) gets the packet
// checks the terminal byte, and send it, the terminal has to
// be connected to the destination router.