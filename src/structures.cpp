#include <iostream>
#include "../include/queue.hpp"
#include "../include/tree.hpp"
#include "../include/router.hpp"

using namespace std;


template <class T> 
Node<T>::Node(T data) {
  this->data = data;
  this->next = nullptr;
}

template <class T>
T& Node<T>::get_data() {
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
    return T();
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

template <class T>
T Queue<T>::get_last() {
  return this->last->get_data();
}

template <class T>
T Queue<T>::get_head() {
  return this->head->get_data();
}


template<class T>
T Queue<T>::search(int key) { 
  Node <terminals_t>* node_temp = this->head;
  while (node_temp != nullptr) {
    if (node_temp->get_data().terminal->get_ID() == key) {
      return node_temp->get_data();
    }
    node_temp = node_temp->get_next();
  }
  cout << "Element not found: " << key <<" [[QUEUE]]" << endl;
  T empty;
  empty.terminal = nullptr;
  return empty;
}

template<class T> //overload for neighbor_t
T& Queue<T>::search_router(int key) { 
  Node<neighbor_t>* node_temp = this->head;
  while (node_temp != nullptr) {
    if (node_temp->get_data().ID == key) {
      return node_temp->get_data();
    }
    node_temp = node_temp->get_next();
  }
  cout << "Router not found: " << key <<" [[QUEUE]]" << endl;
  static T empty;
  empty.router = nullptr;
  return empty;
}

template<class T>
T& Queue<T>::search_router_idx(int index) { 
  Node<neighbor_t>* node_temp = this->head;
  for (int i = 0; i < index; i++) {
    node_temp = node_temp->get_next();
  }
  return node_temp->get_data();
}

template<class T>
T& Queue<T>::search_packet_idx(int index) { 
  Node<Packet>* node_temp = this->head;
  for (int i = 0; i < index; i++) {
    node_temp = node_temp->get_next();
  }
  return node_temp->get_data();
}

template<class T>
T& Queue<T>::search_neighbor(Router *router) { 
  Node<neighbor_t>* node_temp = this->head;
  while (node_temp != nullptr) {
    if (node_temp->get_data().router == router) {
      return node_temp->get_data();
    }
    node_temp = node_temp->get_next();
  }
  cout << "Router not found: " << router->get_name() <<" [[QUEUE]]" << endl;
  static T empty;
  empty.router = nullptr;
  return empty;
}

template<class T>
bool Queue<T>::exists_terminal(int key) { 
  Node<terminals_t>* node_temp = this->head;
  while (node_temp != nullptr) {
    if (node_temp->get_data().terminal->get_ID() == key) {
      return true;
    }
    node_temp = node_temp->get_next();
  }
  return false;
}
template<class T> 
T& Queue<T>::search_packet(int key) { 
  Node<Packet>* node_temp = this->head;
  while (node_temp != nullptr) {
    if (node_temp->get_data().destination == key) {
      cout << "Packet found: " << key <<" [[QUEUE]]" << endl;
      return node_temp->get_data();
    }
    node_temp = node_temp->get_next();
  }
  cout << "Packet not found: " << key <<" [[QUEUE]]" << endl;
  static Packet empty;
  empty.destination = -1;
  return empty;
}

template <class T>
Tree_Node<T>::Tree_Node(T data) : data(data), left(nullptr), right(nullptr) {}

template <class T>
T Tree_Node<T>::get_data() {
  return data;
}

template <class T>
Tree_Node<T>*& Tree_Node<T>::get_left() {
  return left;
}

template <class T>
Tree_Node<T>*& Tree_Node<T>::get_right() {
  return right;
}

template <class T>
void Tree_Node<T>::set_left(Tree_Node<T>* left) {
  this->left = left;
}

template <class T>
void Tree_Node<T>::set_right(Tree_Node<T>* right) {
  this->right = right;
}


template <class T>
class Tree {
  public:
    Tree();
    ~Tree();
    void add(T data);
    void print_tree();
    void delete_node(Tree_Node<T>*& delete_node);

  private:
    Tree_Node<T>* root;
    void insert(Tree_Node<T>*& new_node, T data);
    void print_tree(Tree_Node<T>* node);
};

template <class T>
Tree<T>::Tree() : root(nullptr) {}

template <class T>
Tree<T>::~Tree() {
  delete_node(root);
}

template <class T>
void Tree<T>::add(T data) {
  insert(root, data);
}

template <class T>
void Tree<T>::insert(Tree_Node<T>*& new_node, T data) {
  if (new_node == nullptr) {
    new_node = new Tree_Node<T>(data);
  } else if (data < new_node->get_data()) {
    insert(new_node->get_left(), data);
  } else {
    insert(new_node->get_right(), data);
  }
}

template <class T>
void Tree<T>::print_tree() {
  print_tree(this->root);
  cout << endl;
}

template <class T>
void Tree<T>::print_tree(Tree_Node<T>* node) {
  if (node != nullptr) {
    print_tree(node->get_left());
    cout << node->get_data() << " ";
    print_tree(node->get_right());
  }
}

template <class T>
void Tree<T>::delete_node(Tree_Node<T>*& d_node) {
  if (d_node != nullptr) {
    delete_node(d_node->get_left());
    delete_node(d_node->get_right());
    delete d_node;
  }
}