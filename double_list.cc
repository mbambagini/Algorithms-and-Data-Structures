//This file contains the declaration and implementation of a double-linked list

#include <iostream>
#include <assert.h>
#include <set>

using namespace std;

//This class implements a simple double-linked list
//The implementation implicitly assumes that there is a constructor of T which
//accepts an int as input (for handling errors: to avoid exceptions)
template <class T>
class MyList {
 public:

  //insert a new element at the list start
  //complexity O(1)
  void pushFront (T value);
  
  //insert a new element at the list end
  //complexity O(1)
  void pushBack (T value);

  //delete and return the first element of the list
  //complexity O(1)
  T popFront ();
  
  //delete and return the last element of the list
  //complexity O(1)
  T popBack ();

  //insert before an specific element 
  //complexity O(n)
  bool insertBefore (T value, T before);
  
  //remove an element of the list
  //complexity O(n)
  bool remove(T value);
  
  //return if value is present in the list
  //complexity O(n)
  bool search(T value);

  //count the number of instances equal to value
  //complexity O(n)
  int count(T value);

  //return the number of elements in the list
  //complexity O(1)
  int size() {
    return num_nodes;
  }

  //return if there is only one instance of value
  //complexity O(n)
  bool unique (T value);

  //return if there are any duplicates in the list
  //time complexity O(n) - space complexity O(n)
  bool anyDuplicate ();

  //return the i-th element 
  //complexity O(n)
  T at(int i);

  MyList(): head(NULL), tail(NULL), num_nodes(0) {}

  ~MyList() {
    destroy();
  }

 private:
  class Node {
   public:
    T val;
	Node *next;
	Node *prev;
  };

  //the list is erased
  //complexity O(n)
  void destroy();

  //number of nodes in the list
  int num_nodes;

  //head of the list
  Node *head;

  //tail of the list
  Node *tail;
};

template<class T>
void MyList<T>::destroy () {
  while (head != NULL) {
    Node *n = head;
	head = head->next;
	delete n;
	num_nodes--;
  }
  tail = NULL;
}

template<class T>
T MyList<T>::at (int i) {
  int j = 0;
  Node *ptr = head;

  while (ptr != NULL && j<i) {
    ptr = ptr->next;
	j++;
  }

  if (ptr == NULL)
    return -1;

  return ptr->val;
}

template<class T>
bool MyList<T>::insertBefore (T value, T before) {
  //empty list
  if (head == NULL)
    return false;

  //generic case
  Node *ptr = head;
  while(ptr != NULL) {
    if (ptr->val == before) {
	  
      Node *n = new Node;
	  n->val = value;
      n->prev = ptr->prev;
	  n->next = ptr;
	  ptr->prev = n;
	  if (head == ptr)
	    head = n;
      if (n->prev != NULL)
	    n->prev->next = n;
	  num_nodes++;
	  
	  return true;
    }
	ptr = ptr->next;
  }

  return false;  
}

template<class T>
bool MyList<T>::remove(T value) {
  //empty list
  if (head == NULL)
    return false;

  //generic case
  Node *ptr = head;
  while (ptr != NULL) {
    if (ptr->val == value) {
	  if (ptr->next != NULL)
	    ptr->next->prev = ptr->prev;
      if (ptr->prev != NULL)
	    ptr->prev->next = ptr->next;
	  delete ptr;
	  num_nodes--;
      return true;
	}
	ptr = ptr->next;
  }

  return false;
}

template<class T>
bool MyList<T>::search(T value) {
  Node *n = head;

  while (n != NULL) {
    if (n->val == value)
	  return true;
	n = n->next;
  }

  return false;
}

template<class T>
int MyList<T>::count(T value) {
  Node *n = head;
  int cnt = 0;

  while (n != NULL) {
    if (n->val == value)
	  cnt++;
	n = n->next;
  }

  return cnt;
}

template<class T>
bool MyList<T>::unique (T value) {
  Node *n = head;
  int cnt = 0;
  
  while (n != NULL) {
	if (n->val == value && ++cnt>1)
	  return false;
	n = n-> next;
  }

  if (cnt == 1)
    return true;
  return false;
}

template <class T>
bool MyList<T>::anyDuplicate () {
  set<T> found_values;
  Node *n = head;

  while(n != NULL) {
    if (found_values.find(n->val) != found_values.end())
	  return true;
	found_values.insert(n->val);
    n = n->next;
  }

  return false;
}

template<class T>
void MyList<T>::pushFront (T value) {
  Node *tmp = new Node;

  tmp->val = value;
  tmp->next = head;
  tmp->prev = NULL;
  if (head != NULL)
    head->next = tmp;
  head = tmp;

  //empty list
  if (tail == NULL)
    tail = head;

  num_nodes++;
}

template<class T>
void MyList<T>::pushBack (T value) {
  Node *n = new Node;

  n->val = value;
  n->next = NULL;
  n->prev = tail;
  if (tail != NULL)
    tail->next = n;

  num_nodes++;
  tail = n;

  if (head == NULL)
    head = tail;
}

template<class T>
T MyList<T>::popFront () {
  //empty list
  if (head == NULL)
    return -1;

  //generic case
  T ret = head->val;
  Node *n = head;
  head = head->next;
  if (n->next != NULL)
    n->next->prev = NULL;
  if (head == NULL)
    tail = NULL;
  num_nodes--;
  delete n;

  return ret;
}

template<class T>
T MyList<T>::popBack () {
  //empty list
  if (tail == NULL)
    return -1;

  //generic case
  T t = tail->val;
  Node *n = tail;
  if (tail->prev != NULL)
    tail->prev->next = NULL;
  tail = tail->prev;
  if (tail == NULL)
    head = NULL;
  delete n;
  num_nodes--;

  return t;
}

int main () {
  MyList<int> mylist;

  //push  
  mylist.pushFront(20);
  mylist.pushFront(10);
  mylist.pushBack(30);
  mylist.pushBack(40);
  assert(mylist.at(0)==10);
  assert(mylist.at(1)==20);
  assert(mylist.at(2)==30);
  assert(mylist.at(3)==40);

  //pop
  assert(mylist.popFront()==10);
  assert(mylist.popBack()==40);

  //insertBefore  
  assert(mylist.insertBefore(25, 30)==true);
  assert(mylist.insertBefore(25, 40)==false);

  //test search functions
  assert(mylist.count(30)==1);
  mylist.pushBack(30);
  assert(mylist.count(30)==2);
  assert(mylist.search(25));
  assert(!mylist.search(40));

  //remove/unique/duplicates
  assert(mylist.size()==4);
  assert(mylist.anyDuplicate()==true);
  assert(mylist.unique(20)==true);
  assert(mylist.unique(30)==false);
  mylist.remove(30);
  assert(mylist.anyDuplicate()==false);
  assert(mylist.unique(30)==true);
  assert(mylist.size()==3);
  assert(mylist.at(0)==20);
  assert(mylist.at(1)==25);
  assert(mylist.at(2)==30);

  return 0;
}
