//This file contains declaration and implementation of a generic list
//lists works better than array to handle data whose number varies 
//significantly (at any time the allocated memory is equal to the amount
//of requried data and the maximum number of element is not strictly
//bounded)

#include <iostream>
#include <assert.h>
#include <set>

using namespace std;

//This class implements a simple single-linked list
template <class T>
class MyList {
 public:

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

 private:
  class Node {
   public:
    T val;
	Node *next;
  };

  //number of nodes in the list
  int num_nodes;

  //head of the list
  Node *head;
};

template<class T>
T MyList<T>::at (int i) {
  int j = 0;
  Node *ptr = head;

  while (ptr != NULL && j<i) {
    ptr = ptr->next;
	j++;
  }

  if (ptr == NULL)
    return 0;

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
  if (head == NULL)
    return false;

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
  if (head == NULL)
    return false;

  if (head->val == value) {
    Node *n = head;
	head = head->next;
    delete n;
	num_nodes--;
	return true;
  }

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

  return 0;
}
