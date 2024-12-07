#include <iostream>
using namespace std;

template <class T>
class Tree_Node {
  public:
    Tree_Node(T data);
    T get_data();
    Tree_Node<T>*& get_left();
    Tree_Node<T>*& get_right();
    void set_left(Tree_Node<T>* left);
    void set_right(Tree_Node<T>* right);

  private:
    T data;
    Tree_Node<T>* left;
    Tree_Node<T>* right;
};

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