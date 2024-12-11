#pragma once
#include <iostream>
#include <bitset>
#include "queue.hpp"

#define BYTES_PER_IP 2
#define BYTE 8

#define MAX_PACKET_SIZE 8   // in this example, every packet can have only 8 characters

using namespace std;

typedef bitset<BYTES_PER_IP * BYTE> IP;

typedef string Data;

typedef struct {
  Data data;
  IP destination;
  bool last_package; // if the packet is the last packet of the page
} Packet;

typedef struct {
  IP destination;
  Data data;
} Page;


// TODO: Every packet has a destination IP, so 
// router recieves a packet and checks where to send it
// when the destination router (first byte of IP) gets the packet
// checks the terminal byte, and send it, the terminal has to
// be connected to the destination router.
