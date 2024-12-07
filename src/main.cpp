#include <iostream>
#include "../include/queue.hpp"

using namespace std;


int main ()
{
  Queue<string> q;
  q.push("hola");
  q.push("soy");
  q.push("emi");
  q.print_queue();
  q.pop();
  q.print_queue();
  return EXIT_SUCCESS;
}

