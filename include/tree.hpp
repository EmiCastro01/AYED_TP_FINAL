#include <iostream>
using namespace std;

template <class T> 
class Tree_Node {
  public:
    Tree_Node(T data);
    T get_data();
    Tree_Node* get_left();
    Tree_Node* get_right();
    void set_left(Tree_Node* left);
    void set_right(Tree_Node* right);
  private:
    T data;
    Tree_Node* left;
    Tree_Node* right;
};

template <class T>
Tree_Node<T>::Tree_Node(T data) {
  this->data = data;
  this->left = nullptr;
  this->right = nullptr;
}

template <class T>
T Tree_Node<T>::get_data() {
  return this->data;
}

template <class T>
Tree_Node<T>* Tree_Node<T>::get_left() {
  return this->left;
}

template <class T>
Tree_Node<T>* Tree_Node<T>::get_right() {
  return this->right;
}

template <class T>
void Tree_Node<T>::set_left(Tree_Node* left) {
  this->left = left;
}

template <class T>
void Tree_Node<T>::set_right(Tree_Node* right) {
  this->right = right;
}

template <class T>
class Tree {
  public:
    Tree();
    void insert(T data); // this has to run logic to insert the data in the right place
    void print_tree();
  private:
    Tree_Node<T>* root;
    void print_tree(Tree_Node<T>* node);
    
};

template <class T>
Tree<T>::Tree() {
  this->root = nullptr;
}

template <class T>
void Tree<T>::insert(T data) {
  Tree_Node<T>* new_node = new Tree_Node<T>(data);
  if (this->root == nullptr) {
    this->root = new_node;
  } else {
    Tree_Node<T>* node_temp = this->root;
    while (node_temp != nullptr) {
      if (data < node_temp->get_data()) {
        if (node_temp->get_left() == nullptr) {
          node_temp->set_left(new_node);
          break;
        } else {
          node_temp = node_temp->get_left();
        }
      } else {
        if (node_temp->get_right() == nullptr) {
          node_temp->set_right(new_node);
          break;
        } else {
          node_temp = node_temp->get_right();
        }
      }
    }
  }
}

template <class T>
void Tree<T>::print_tree() {
  print_tree(this->root);
  cout << "Printing tree" << endl;
}

template <class T>
void Tree<T>::print_tree(Tree_Node<T>* node) {
  if (node != nullptr) {
    print_tree(node->get_left());
    cout << node->get_data() << endl;
    print_tree(node->get_right());
  }
}
