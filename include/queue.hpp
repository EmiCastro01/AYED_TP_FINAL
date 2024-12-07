#include <iostream>
using namespace std;

template <class T> class Node {
  public:
    Node(T data);
    T get_data();
    Node<T>* get_next();
    void set_next(Node<T>* next);
  private:
    T data;
    Node<T>* next;
};

template <class T> 
Node<T>::Node(T data) {
  this->data = data;
  this->next = nullptr;
}

template <class T>
T Node<T>::get_data() {
  return this->data;
}

template <class T>
Node<T>* Node<T>::get_next() {
  return this->next;
}

template <class T>
void Node<T>::set_next(Node<T>* next) {
  this->next = next;
}


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
  
  private:
    int queue_size;
    Node<T>* head;
    Node<T>* last;
};


template <class T>
Queue<T>::Queue() {
  this->queue_size = 0;
  this->head = nullptr;
  this->last = nullptr;
}

template <class T>
void Queue<T>::push(T data) {
  Node<T>* new_node = new Node<T>(data);
  if (this->head == nullptr) {
    this->head = new_node;
    this->last = new_node;
  } else {
    new_node->set_next(this->head);
    this->head = new_node;
  }
  this->queue_size++;
}

template <class T>
T Queue<T>::pop() {
  if(this->is_empty() == true) {
    cout << "Queue is empty" << endl;
    return 0;
  } else {
    Node<T>* node_temp = this->head;  
    if(this->head == this->last) {
      T popped_data = this->head->get_data();
      delete this->head;
      this->head = nullptr;
      this->last = nullptr;
      this->queue_size--;
      return popped_data;
    }
    while (node_temp->get_next() != this->last) {
      node_temp = node_temp->get_next();
    }
    this->last = node_temp;
    T popped_data = node_temp->get_next()->get_data();
    delete this->last->get_next();
    this->last->set_next(nullptr);
    this->queue_size--;
    return popped_data;
  }
}

template <class T>
void Queue<T>::print_queue()
{
  Node<T>* node_temp = this->head;
  cout << "[";
  while (node_temp != nullptr) {
    cout << node_temp->get_data() << ", ";
    node_temp = node_temp->get_next();
  }
  cout << "]" << endl;
}

template <class T>
bool Queue<T>::is_empty() {
  return this->queue_size == 0;
}

template <class T>
int Queue<T>::size() {
  return this->queue_size;
}