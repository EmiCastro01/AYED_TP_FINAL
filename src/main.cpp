#include <iostream>
#include "../include/queue.hpp"
#include "../include/tree.hpp"
using namespace std;


int main ()
{
  Tree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.print_tree();
  

  return EXIT_SUCCESS;
}

