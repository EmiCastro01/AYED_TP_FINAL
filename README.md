# AYED_TP_FINAL


# Justify Trade-off Time-Space

Network class has an array of Routers, but no array for Terminals.
But network must have information about terminals. So, for returning a Terminal, we decided to iterate the array of Routers (that has minimun size compare to amount of Terminals) and, on each Router, iterate the Queue of Termials, searching on this process
the Terminal to return.
We have needed to decided a Trade-off solution between this, and just making an array.

We had a similar situation with the regenerate_page method. We decided to make a pipeline solution.

## Comparison
  Terminal Array Option is more effective at time resource, which is better if amount of
  terminals are near the max, but, if this amount is low, then memory is occupated anyways
  with the 5K locations that are needed for the max amount. (256 * 256)
  List of Terminals on Routers Array is more effective at space, due to dynamic allocation, but less effective at time.

## Why we decided second option
  Because the network is not gonna run on a real server with a lot of memory space,
  but is on a PC, so we priorized that resource.


## Sort Type Justify

We decieded to use Bubble Sort beacuse of simplicity. We use the sort on index for packets,
on regenerate page, the number of packets is always less than a Byte, so there is no conflicts on time resource by using Bubble Sort.

## Why congestion matrix does not increment nodes when packets are sent

Because every router takes just one packet from entry gate on every cycle, and every channel
has more than 1 of band width, so, on one cycle, the packets is pop out of the queue.

## Adjacency Matrix is used twice

On reset, adjacency Matrix is randomly load with costs (band width), this is the same address memory
that is used to load congestion on the net. Costs are stored on every router-neighbor connection once (on reset). Anyways, user can display it with debug-mode of Simulator.

## Terminals are generated randomly

Terminals are generated randomly. That means that a router can have ONLY client sources, or ONLY receiver terminals. That isn't a problem beacuse a Terminal have always a router, so a receiver terminal must have a path to receive data.