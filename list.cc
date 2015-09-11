//This file contains the declaration and implementation of a generic list
//Lists work better than array to handle data whose number varies significantly
//(at any time the allocated memory is equal to the amount of required data and
//the maximum number of elements is not strictly bounded)

//many functions may seem useless, but their duty consists of making practise

#include <iostream>
#include <assert.h>
#include <set>

using namespace std;

//This class implements a simple single-linked list
//The implementation implicitly assumes that there is a constructor of T which
//accepts an int as input (for handling errors: to avoid exceptions)
template <class T>
class MyList {
 public:

  //insert a new element at the list start
  //complexity O(1);
  void pushFront (T value) {
    insert(value);
  }
  
  //insert a new element at the list end
  //complexity O(n)
  void pushBack (T value);
  
  //delete and return the first element of the list (note that the functions
  //top and pop should have been implemented to avoid data inconsistency -
  //however it is out of the scope of this code)
  //complexity O(1)
  T popFront ();
  
  //delete and return the last element of the list
  //complexity O(n)
  T popBack ();

  //insert value as first element in the list
  //complexity O(1)
  void insert(T value);
  
  //insert value after the first element equal to after
  //complexity O(n)
  bool insertAfter(T value, T after);
  
  //remove the first element equal to value
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

  MyList(): head(NULL), num_nodes(0) {}

  ~MyList() {
    destroy();
  }

 private:
  class Node {
   public:
    T val;
	Node *next;
  };

  //the list is erased
  //complexity O(n)
  void destroy();
  
  //number of nodes in the list
  int num_nodes;

  //head of the list
  Node *head;
};

template<class T>
void MyList<T>::destroy (int i) {
  while (head != NULL) {
    Node *n = head;
	head = head->next;
	delete n;
	num_nodes--;
  }
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
void MyList<T>::insert (T value) {
  Node *tmp = new Node;

  tmp->val = value;
  tmp->next = head;
  head = tmp;

  num_nodes++;
}

template<class T>
bool MyList<T>::insertAfter(T value, T after) {
  //empty list
  if (head == NULL)
    return false;

  //generic case
  Node tmp = head;
  while (tmp != NULL) {
    if (tmp->value == after && (tmp->next == NULL || tmp->value != after) ) {
	  Node *n = new Node;
	  n->val = value;
	  n->next = tmp->next;
	  tmp->next = n;
	  num_nodes++;
	  return true;
    }
	tmp = tmp->next;
  }

  return false;
}

template<class T>
bool MyList<T>::remove(T value) {
  //empty list
  if (head == NULL)
    return false;

  //first element is the wanted
  if (head->val == value) {
    Node *n = head;
	head = head->next;
    delete n;
	num_nodes--;
	return true;
  }

  //generic case
  Node *tmp = head;
  while (tmp->next != NULL) {
    if (tmp->next->val == value) {
	  Node *n = tmp->next->next;
	  delete tmp->next;
	  tmp->next = n;
	  num_nodes--;
      return true;
	}
	tmp = tmp->next;
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
void MyList<T>::pushBack (T value) {
  Node *n = new Node;
  n->val = value;
  n->next = NULL;

  //empty list
  if (head == NULL) {
    head = n;
	num_nodes++;
	return;
  }

  //generic case
  Node *ptr = head;
  while (ptr->next != NULL)
    ptr = ptr->next;

  ptr->next = n;
  num_nodes++;
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
  num_nodes--;
  delete n;

  return ret;
}

template<class T>
T MyList<T>::popBack () {
  //empty list
  if (head == NULL)
    return -1;

  //only one element
  if (head->next == NULL) {
    T t = head->val;
	Node *n = head;
	head = NULL;
	delete n;
	num_nodes--;
	return t;
  }

  //generic case
  Node *ptr = head;
  while (ptr->next->next != NULL)
    ptr = ptr->next;

  T t = ptr->next->val;
  Node *n = ptr->next;
  ptr->next = ptr->next->next;
  delete n;
  num_nodes--;
  return t;
}

int main () {
  MyList<int> mylist;
  
  mylist.insert(10);
  mylist.insert(20);
  mylist.insert(30);
  mylist.insert(30);

  //test insert and retrieve functions
  assert(mylist.at(0)==30);
  assert(mylist.at(1)==30);
  assert(mylist.at(2)==20);
  assert(mylist.at(3)==10);

  //test search functions
  assert(mylist.count(30)==2);
  assert(mylist.search(10));
  assert(!mylist.search(15));

  //test remove function
  assert(mylist.size()==4);
  mylist.remove(30);
  assert(mylist.size()==3);
  assert(mylist.at(0)==30);
  assert(mylist.at(1)==20);
  assert(mylist.at(2)==10);

  //unique
  assert(mylist.anyDuplicate()==false);
  mylist.insert(20);
  assert(mylist.unique(10)==true);
  assert(mylist.unique(20)==false);
  assert(mylist.anyDuplicate()==true);

  //push and pop
  MyList<int> mylist2;
  mylist2.insert(20);
  mylist2.pushBack(30);
  mylist2.pushFront(10);
  assert(mylist2.at(0)==10);
  assert(mylist2.at(1)==20);
  assert(mylist2.at(2)==30);
  assert(mylist2.size()==3);
  assert(mylist2.popBack()==30);
  assert(mylist2.popFront()==10);
  assert(mylist2.size()==1);
  assert(mylist2.popBack()==20);
  assert(mylist2.size()==0);
  
  return 0;
}
