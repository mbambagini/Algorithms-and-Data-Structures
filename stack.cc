//this file contains the declaration and implementation of a stack

#include <iostream>
#include <assert.h>

using namespace std;

//Stack data structure
//The type T must implement a casting from int to T to support error conditions
//The implementation relies on a single-linked list. An alternative can exploit
//arrays. Arrays do not have to allocate memory every time but they are fixed in
//size (or they have to allocate additional memory when needed)
template <class T>
class Stack {
 public:
 
  //add an element on top of the stack
  //complexity O(1)
  void push (T value);

  //retrieve the last element
  //complexity O(1)
  T pop ();

  //return the number of elements in the stack
  //complexity O(1)
  int size () {
    return num_nodes;
  }

  Stack (): head(NULL), num_nodes(0) {}

 private:
  class Node {
   public:
    T val;
    Node* next;
  };

  int num_nodes;

  Node* head;
};

template<class T>
void Stack<T>::push (T value) {
  Node *n = new Node;
  n->val = value;
  n->next = head;
  head = n;
  num_nodes++;
}

template<class T>
T Stack<T>::pop () {
  if (head == NULL)
    return -1;

  Node *n = head;
  T value = n->val;
  head = head->next;
  delete n;
  num_nodes--;

  return value;
}

 
int main () {
  Stack<int> stack;
  
  assert(stack.size()==0);
  stack.push(1);
  assert(stack.size()==1);
  stack.push(10);
  assert(stack.size()==2);
  stack.push(5);
  assert(stack.size()==3);

  assert(stack.pop()==5);
  assert(stack.size()==2);
  assert(stack.pop()==10);
  assert(stack.size()==1);
  assert(stack.pop()==1);
  assert(stack.size()==0);
  assert(stack.pop()==-1);

  return 0;
}
