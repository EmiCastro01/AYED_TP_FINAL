#pragma once
#include <bitset>
#include <iostream>

#include "queue.hpp"

#define BYTES_PER_IP 2
#define BYTE 8

#define MAX_PACKET_SIZE 8

using namespace std;

typedef bitset<BYTES_PER_IP * BYTE> IP;

typedef string Data;

typedef struct {
    Data data;
    int ID;  // to identificate the page that the packet belongs
    IP destination;
    int index;          // index of the packet in the page
    bool last_package;  // if the packet is the last packet of the page
    int size;
} Packet;

typedef struct {
    int ID;  // to identificate the page
    IP destination;
    Data data;
} Page;

// TODO: Every packet has a destination IP, so
// router recieves a packet and checks where to send it
// when the destination router (first byte of IP) gets the packet
// checks the terminal byte, and send it, the terminal has to
// be connected to the destination router.
