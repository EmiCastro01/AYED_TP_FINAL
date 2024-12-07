#include <iostream>
#include "../include/queue.hpp"

using namespace std;


int main ()
{
  Queue<string> q;
  q.push("hola");
  q.push("soy");
  q.push("emi");
  cout << q.size() << endl;
  q.print_queue();
  q.pop();
  q.print_queue();
  cout << q.size() << endl;
  q.pop();
  

  return EXIT_SUCCESS;
}

