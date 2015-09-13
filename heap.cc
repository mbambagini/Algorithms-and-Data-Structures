//This file provides an implementation of the head data structure.
//The heap is one of the possible implementation of the priority queues which
//let users insert value and return the one with highest priority.
//There are several possible implementation whose performance is the follwing:
//            
//         insertion   retrieving   erasing   getting   priority   union
//                     maximum                the max   change
//
//sorted
//array        N           1            N         1         N        N
//
//unsorted
//array        N           N            1         N         1        N
//
//heap        logN        logN         logN       1        logN      N
//
//binomial
//queue       logN        logN         logN      logN      logN      logN
//
//The heap is implemented as a binary tree whose each node has a priority higher
//than the pririties of its sub-trees (represented within an array)

#include <iostream>
#include <assert.h>

using namespace std;


template <class T>
class Heap {
 public:

  //insert a new element in the heap
  bool insert(T val);

  //remove and return the element with highest priority
  T getMax ();

  //return if there is no more space
  int isFull() {
    return (num_nodes >= max_num_nodes);
  }

  //construct the heap with maximum n nodes
  Heap (int n) {
    max_num_nodes = n;
    a = new T[max_num_nodes];
    num_nodes = 0;
  }

  virtual ~Heap() {
    if (a != NULL)
      delete[] a;
  }

 private:

  //main array
  T* a;

  //it contains the number of actual nodes
  int num_nodes;

  //it contains the maximum number of nodes
  int max_num_nodes;

  //fix the position of the k-th node when its priority is increased
  //It is eventually changed with its father
  void fixUp (int k);

  //fix the position of the k-th node when its priority is decreased
  void fixDown(int k);

  //switch the position of two nodes
  void exchange(int id1, int id2) {
    T tmp = a[id1];
    a[id1] = a[id2];
    a[id2] = tmp;
  }
};

template<class T>
void Heap<T>::fixUp (int k) {
  //k/2 is the index of the father of k-th node
  while (k >= 0 && a[k/2] < a[k]) {
    exchange(k, k/2);
    k = k/2;
  }
}

template<class T>
void Heap<T>::fixDown(int k) {
  //k-th node's sons are at position 2*k and 2*k+1
  while((2*k) < num_nodes) {
    int son = 2*k;
    //pick son which highest priority
    if (son < (num_nodes-1) && a[son] < a[son+1])
      son++;
    if (a[k] >= a[son])
      break;
    exchange(k, son);
    k = son;
  }
}

template<class T>
bool Heap<T>::insert(T val) {
  if (num_nodes >= max_num_nodes)
    return false;

  a[num_nodes] = val;
  fixUp(num_nodes);
  num_nodes++;

  return true;
}

template<class T>
T Heap<T>::getMax () {
  if (num_nodes == 0)
    return -1;

  T val = a[0];
  exchange(0, num_nodes-1);
  num_nodes--;
  fixDown(0);

  return val;
}

#define ARRAY_SIZE 	20

int main () {
  Heap<int> heap(ARRAY_SIZE);
  int ar[ARRAY_SIZE] = {3, 20, 1, 19, 8, 5, 13, 10, 18, 7, 12, 9, 14, 4, 2, 15,
                        6, 17, 11, 16};

  for (int i = 0; i < ARRAY_SIZE; i++)
    heap.insert(ar[i]);

  for (int i = ARRAY_SIZE; i > 0; i--)
    assert(heap.getMax()==i);

  return 0;
}
