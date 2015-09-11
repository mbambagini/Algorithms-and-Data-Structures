//this file contains the declaration and implementation of a queue (FIFO)

#include <iostream>
#include <assert.h>

using namespace std;

//Queue data structure
//The type T must implement a casting from int to T to support error conditions
//The implementation relies on a double-linked list. An alternative can exploit
//arrays. Arrays do not have to allocate memory every time but they are fixed in
//size (or they have to allocate additional memory when needed)
template <class T>
class Queue {
 public:
  //add an element at the end of the queue
  //complexity O(1)
  void push (T value);

  //retrieve the first element
  //complexity O(1)
  T pop ();

  //return the number of elements in the queue
  //complexity O(1)
  int size () {
    return num_nodes;
  }

  Queue (): head(NULL), tail(NULL), num_nodes(0) {}

 private:
  class Node {
   public:
    T val;
    Node* next;
	Node* prev;
  };

  int num_nodes;

  Node* head;
  Node* tail;
};

template<class T>
void Queue<T>::push (T value) {
  Node *n = new Node;
  n->val = value;
  n->prev = NULL;
  n->next = head;
  if (head != NULL)
    head->prev = n;
  head = n;
  if (tail == NULL)
    tail = n;
  num_nodes++;
}

template<class T>
T Queue<T>::pop () {
  if (tail == NULL)
    return -1;

  Node *n = tail;
  T value = n->val;
  if (n->prev != NULL) {
    n->prev->next = NULL;
    tail = n->prev;
  } else {
    tail = NULL;
	head = NULL;
  }
  delete n;
  num_nodes--;

  return value;
}

 
int main () {
  Queue<int> queue;

  assert(queue.size()==0);
  queue.push(1);
  assert(queue.size()==1);
  queue.push(10);
  assert(queue.size()==2);
  queue.push(5);
  assert(queue.size()==3);

  assert(queue.pop()==1);
  assert(queue.size()==2);
  assert(queue.pop()==10);
  assert(queue.size()==1);
  assert(queue.pop()==5);
  assert(queue.size()==0);
  assert(queue.pop()==-1);

  return 0;
}
