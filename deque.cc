//this file contains the declaration and implementation of a deque (insertion
//and deletion from both sides)

#include <iostream>
#include <assert.h>

using namespace std;

//Deque data structure
//The type T must implement a casting from int to T to support error conditions
//The implementation relies on a double-linked list.
template <class T>
class Deque {
 public:

  //add an element as first one
  //complexity O(1)
  void pushFront (T value);
  
  //add an element as last one
  //complexity O(1)
  void pushBack (T value);

  //retrieve the first element
  //complexity O(1)
  T popFront ();

  //retrieve the last element
  //complexity O(1)
  T popBack ();

  //return the number of elements in the queue
  //complexity O(1)
  int size () {
    return num_nodes;
  }

  Deque (): head(NULL), tail(NULL), num_nodes(0) {}

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
void Deque<T>::pushFront (T value) {
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
void Deque<T>::pushBack (T value) {
  Node *n = new Node;
  n->val = value;
  n->next = NULL;
  n->prev = tail;
  if (tail != NULL)
    tail->next = n;
  tail = n;
  if (head == NULL)
    head = n;
  num_nodes++;
}

template<class T>
T Deque<T>::popFront () {
  if (head == NULL)
    return -1;

  Node *n = head;
  T value = n->val;
  if (n->next != NULL) {
    n->next->prev = NULL;
    head = n->next;
  } else {
    tail = NULL;
	head = NULL;
  }
  delete n;
  num_nodes--;

  return value;
}

template<class T>
T Deque<T>::popBack () {
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
  Deque<int> queue;

  assert(queue.size()==0);
  queue.pushFront(1);
  assert(queue.size()==1);
  queue.pushFront(2);
  assert(queue.size()==2);
  queue.pushFront(3);
  assert(queue.size()==3);
  queue.pushBack(6);
  assert(queue.size()==4);
  queue.pushBack(7);
  assert(queue.size()==5);
  queue.pushBack(8);
  assert(queue.size()==6);

  assert(queue.popFront()==3);
  assert(queue.size()==5);
  assert(queue.popFront()==2);
  assert(queue.size()==4);
  assert(queue.popFront()==1);
  assert(queue.size()==3);
  assert(queue.popFront()==6);
  assert(queue.size()==2);
  assert(queue.popBack()==8);
  assert(queue.size()==1);
  assert(queue.popBack()==7);
  assert(queue.size()==0);
  assert(queue.popFront()==-1);

  return 0;
}
