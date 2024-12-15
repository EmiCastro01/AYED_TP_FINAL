#pragma once
#include <iostream>


using namespace std;

//-----------------NODE-----------------
template <class T> class Node {
  public:
    Node(T data);
    T& get_data();
    Node<T>* get_next();
    void set_next(Node<T>* next);
  private:
    T data;
    Node<T>* next;
};

//-----------------QUEUE-----------------
template <class T> class Queue {

  public:
    Queue();
    void push(T data);
    T pop();
    T get_last();
    T get_head();
    int size();
    bool is_empty();
    void print_queue();
    T search(int key);
    T& search_router(int key);
    T& search_router_idx(int index);
    T& search_packet(int key);
    T& search_packet_idx(int index);
  
  private:
    int queue_size;
    Node<T>* head;
    Node<T>* last;
};
