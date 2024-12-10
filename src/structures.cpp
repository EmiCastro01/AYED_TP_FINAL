#include <iostream>
#include "../include/queue.hpp"
#include "../include/tree.hpp"

using namespace std;


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

template <class T>
T Queue<T>::get_last() {
  return this->last->get_data();
}

template <class T>
T Queue<T>::get_head() {
  return this->head->get_data();
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