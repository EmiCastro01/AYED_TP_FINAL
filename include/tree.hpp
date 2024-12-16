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
