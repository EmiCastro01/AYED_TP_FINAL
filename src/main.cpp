#include <iostream>
#include "../include/queue.hpp"
#include "../include/tree.hpp"
using namespace std;


int main ()
{
  Tree<int> tree;
  tree.add(5);
  tree.add(3);
  tree.add(7);
  tree.add(2);
  tree.add(4);
  tree.print_tree();

  return EXIT_SUCCESS;
}

