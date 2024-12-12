# AYED_TP_FINAL

This project simulates a system with routers and machines that can transfer
packages of data themselves......

# UPDATES

The project can generate de network between routers, with neighbors. Neighbors are stored on each
router with a queue of neighbor_t structures, that have the ID and cost.
The project can generate router->terminal connections, and generate a queue with
the terminals corresponding of each router. Every terminal has a unique ID.
The project can ask the network to search terminals by ID; so Simulator can operate them
to send data and recieve them.


# Justify Trade-off Time-Space

Network class has an array of Routers, but no array for Terminals.
But network must have information about terminals. So, for returning a Terminal, we decided to iterate the array of Routers (that has minimun size compare to amount of Terminals) and, on each Router, iterate the Queue of Termials, searching on this process
the Terminal to return.
We have needed to decided a Trade-off solution between this, and just making an array.

## Comparison
  Terminal Array Option is more effective at time resource, which is better if amount of
  terminals are near the max, but, if this amount is low, then memory is occupated anyways
  with the 5K locations that are needed for the max amount. (256 * 256)
  List of Terminals on Routers Array is more effective at space, due to dynamic allocation, but less effective at time.

## Why we decided second option
  Because the network is not gonna be runned on a real server with a lot of memory space,
  but is on a PC, so we priorized that resource.


# COMMING FEATURES

The system needs to regenerate the page, and send it to terminal when is regenerated,
based on:
  - The ID of the paket (is the same on the ID of page, so every packet whith the same ID
  belongs to the same page, which has the same ID)
  - If the size of the page equals to amount of packets on queue.
  - If the queue has the last package, this is not comparable with amount of packets, because
  packets can be mixed on queue.
If conditions are true, then create a Page and  send it to the terminal, which must be the packets or page destination IP.


