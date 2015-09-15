//search algorithms look for a key among many records
//functions to be implemented: search, insert, remove, select, show
//implemented algorithms: indexed-key search, sequantial search, binary search and binary search tree

#include <iostream>
#include <sstream>
#include <assert.h>
#include <string>

using namespace std;

//generic interface for search algorithms
template<class K, class V>
class GenericSearch {
 public:
  //return the number of stored records
  virtual int count() = 0;

  //search and return the item with the specified key
  virtual V search (K key) = 0;

  //insert a new element with the specified key
  virtual void insert (K key, V value) = 0;

  //remove the element with the specified key
  virtual void remove (K key) = 0;

  //Return the i-th element
  virtual V select (int i) = 0;
  
  virtual void print(string &s) = 0;
};

////////////////////////////////////////////////////////////////////////////////

//the simplest scenario happens when the keys are integers between 0 and M-1,
//meaning that the key is the index: the field key is useless
//for the sake of simplicity, if the stored key is -1, it means that the actual
//cell is empty
//the complexity is constant but the data structure is not flexible
template<class V>
class IndexedKeySearch : public GenericSearch<int, V> {
 public:
  IndexedKeySearch (int n);

  ~IndexedKeySearch () {
    delete[] buffer;
  }

  //complexity O(1)
  int count () {
    return num_actual_elements;
  }

  //complexity O(1)
  V search (int key) {
    if (key < num_max_elements)
      return buffer[key];
    return -1;
  }

  //complexity O(1)
  void insert (int key, V value) {
    if (key < num_max_elements) {
       if (buffer[key] == -1)
         num_actual_elements++;
       buffer[key] = value;
    }
  }

  //complexity O(1)
  void remove (int key) {
    if (key < num_max_elements) {
      if (buffer[key] != -1)
        num_actual_elements--;
      buffer[key] = -1;
    }
  }

  //complexity O(1)
  V select (int i) {
    return search(i);
  }

  void print(string &s) {
    stringstream ss;
    for (int i = 0; i < num_max_elements; i++)
	  if (buffer[i] != -1)
	    ss<<"("<<i<<", "<<buffer[i]<<") ";
	s = ss.str();
  }
  
 private:
  //it states the maximum number of storable items
  int num_max_elements;

  //it states the actual number of stored items
  int num_actual_elements;

  //array of items
  V *buffer;
};

template<class V>
IndexedKeySearch<V>::IndexedKeySearch (int n) {
  num_actual_elements = 0;
  num_max_elements = n;
  buffer = new V[n];
  for (int i = 0; i < n; i++)
    buffer[i] = -1;
}

////////////////////////////////////////////////////////////////////////////////

//this algorithm search the element sequentially in an array
template<class K, class V>
class SequentialSearch : public GenericSearch<K, V> {
 public:
  SequentialSearch (int n);

  virtual ~SequentialSearch () {
    delete[] buffer;
  }

  //complexity O(1)
  int count () {
    return num_actual_elements;
  }

  //complexity O(N)
  V search (int key);

  //complexity O(N)
  void insert (K key, V value);

  //complexity O(N)
  void remove (K key);

  //complexity O(1)
  V select (int i) {
    return buffer[i].value;
  }

  void print(string &s) {
    stringstream ss;
    for (int i = 0; i < num_actual_elements; i++)
      ss<<"("<<buffer[i].key<<", "<<buffer[i].value<<") ";
	s = ss.str();
  }

 protected:
  //key-value pair
  class Item {
   public:
    K key;
    V value;
  };

  //vector of items
  Item *buffer;

  //maximum number of storable elements
  int num_max_elements;
  
  //actual number of stored elements
  int num_actual_elements;
};

template<class K, class V>
SequentialSearch<K, V>::SequentialSearch (int n) {
  num_actual_elements = 0;
  num_max_elements = n;
  buffer = new Item[n];
  for (int i = 0; i < n; i++)
    buffer[i].key = -1;
}

template<class K, class V>
V SequentialSearch<K, V>::search (int key) {
  for (int i = 0; i < num_actual_elements; i++)
    if (buffer[i].key == key)
      return buffer[i].value;
  return -1;
}

template<class K, class V>
void SequentialSearch<K, V>::insert (K key, V value) {
  if (num_actual_elements == num_max_elements)
    return;
  int i = num_actual_elements++;
  while (i > 0 && key < buffer[i-1].key) {
    buffer[i] = buffer[i-1];
    i--;
  }
  buffer[i].key = key;
  buffer[i].value = value;
}

template<class K, class V>
void SequentialSearch<K, V>::remove (K key) {
  int i = 0;
  for (; i < num_actual_elements; i++)
    if (buffer[i].key == key)
      break;
  if (i == num_actual_elements)
    return;
  for (; i < (num_actual_elements-1); i++)
    buffer[i] = buffer[i+1];
  num_actual_elements--;
}

////////////////////////////////////////////////////////////////////////////////

template<class K, class V>
class BinarySearch : public SequentialSearch<K, V> {
 public:
  BinarySearch(int n) : SequentialSearch<K, V>(n) { }

  //complexity O(logN)
  V search (K key) {
    return search(key, 0, SequentialSearch<K, V>::num_actual_elements-1);
  }

 private:
  V search (K key, int start, int stop);
};

template<class K, class V>
V BinarySearch<K, V>::search (K key, int start, int stop) {
  if (start > stop)
    return -1;
  int m = (stop+start)/2;
  if (SequentialSearch<K, V>::buffer[m].key == key)
    return SequentialSearch<K, V>::buffer[m].value;
  if (SequentialSearch<K, V>::buffer[m].key < key)
    return search(key, m+1, stop);
  return search(key, start, m-1);
}

////////////////////////////////////////////////////////////////////////////////


//in media O(logN), nel caso peggiore O(N)
//per bilanciare:
//- metodi randomizzati: introducono valori random per allontanarsi dal caso
//  peggiore (BST randomizzati e skip list)
//- metodi ammortizzati: poche modifiche (splay BST)
//. metodi ottimizzati: forniscono garanzie (2-3-4 top-down e red-black)
//each node has a key higher than keys in the left sub-tree and lower than ones
//in the right sub-tree
template<class K, class V>
class BinarySearchTree : public GenericSearch<K, V> {
 public:
  BinarySearchTree () {
    num_actual_elements = 0;
    head = NULL;
  }

  ~BinarySearchTree () {
    //todo
  }

  //complexity O(1)
  int count () {
    return num_actual_elements;
  }

  //complexity O(logN)
  V search (int key) {
    return search(key, head);
  }

  //complexity O(logN);
  void insert (K key, V value) {
    if (head == NULL) {
      head = new BSTNode(key, value);
      num_actual_elements = 1;
      return;
    }
    insert(key, value, head);
  }

  void print(string &s) {
    print(s, head);
  }

  void remove (K key) {
    if (head == NULL)
	  return;
	remove(key, head);
  }

  //complexity O(1)
  V select (int i) {
    //int j = i;
    //return select(j, head);
	return -1;
  }
/*  V select (int &i, BSTNode* ptr) {
    if (ptr == 0)
      return -1;
    V val = select(i, ptr->left);
    if (val != -1)
      return val;
    i--;
    if (i == 0)
      return ptr->item.value;
    val = select(i, ptr->left);
    if (val != -1)
      return val;
  }
*/
 private:

  class Item {
   public:
    K key;
    V value;
  };

  class BSTNode {
   public:
    Item item;
    BSTNode *left;
    BSTNode *right;
    BSTNode (K key, V value) {
      item.key = key;
      item.value = value;
      right = left = NULL;
    }
  };

  void print (string &s, BSTNode* ptr);
  
  void insert (K key, V value, BSTNode *ptr);  

  V search (K key, BSTNode* ptr);

  void remove (K key, BSTNode*& ptr);
  
  void removeMin (BSTNode* &ptr, Item &item);

  //
  BSTNode *head;

  //it states the actual number of nodes in the BST
  int num_actual_elements;

};

template<class K, class V>
void BinarySearchTree<K, V>::print (string &s, BSTNode* ptr) {
  stringstream ss;
  if (ptr == NULL)
    return;
  print(s, ptr->left);
  ss<<s<<"("<<ptr->item.key<<", "<<ptr->item.value<<") ";
  s = ss.str();
  print(s, ptr->right);
}

//if ptr points to the element to be removed:
//- if it is a leave, remove it
//- if it has only a son, substitute it with the son
//- it it has two sons, substitite the node with the minimum in the left subtree
template<class K, class V>
void BinarySearchTree<K, V>::remove (K key, BSTNode* &ptr) {
  if (ptr == NULL)
    return;

  if (ptr->item.key != key) {
    remove(key, ptr->left);
	remove(key, ptr->right);
	return;
  }

  BSTNode *n = ptr;
  if (ptr->left == NULL && ptr->right == NULL) {
	ptr = NULL;
    delete n;
	return;
  }
  if (ptr->left == NULL || ptr->right == NULL) {
    ptr = (ptr->left == NULL)? ptr->right : ptr->left;
	delete n;
	return;
  }
  Item item;
  removeMin(ptr->right, item);
  ptr->item = item;
  num_actual_elements--;
}

template<class K, class V>
void BinarySearchTree<K, V>::removeMin (BSTNode* &ptr, Item &item) {
  if (ptr == NULL)
    return;
  if (ptr->left != NULL)
    return removeMin(ptr->left, item);
  item = ptr->item;
  if (ptr->right != NULL)
    ptr = ptr->right;
  else {
    BSTNode *n = ptr;
    ptr = NULL;
    delete n;
  }
}

template<class K, class V>
void BinarySearchTree<K, V>::insert (K key, V value, BSTNode *ptr) {
  if (key == ptr->item.key) {
    ptr->item.value = value;
    return;
  }
  if (key > ptr->item.key) {
    //right sub-tree
    if (ptr->right == NULL) {
      ptr->right = new BSTNode(key, value);
      num_actual_elements++;
      return;
    } else
      insert(key, value, ptr->right);
  } else {
    //left sub-tree
    if (ptr->left == NULL) {
      ptr->left = new BSTNode(key, value);
      num_actual_elements++;
      return;
    } else
      insert(key, value, ptr->left);
  }
}
  
template<class K, class V>
V BinarySearchTree<K, V>::search (K key, BSTNode* ptr) {
  if (ptr == NULL)
    return -1;
  if (ptr->item.key == key)
    return ptr->item.value;
  if (ptr->item.key > key)
    return search(key, ptr->left);
  return search(key, ptr->right);
}

////////////////////////////////////////////////////////////////////////////////

void execute (GenericSearch<int, int>* t) {
  string s;
  t->insert(0, 3);
  t->insert(1, 2);
  t->insert(4, 8);
  t->insert(7, 7);
  t->insert(2, 1);
  t->insert(3, 5);
  t->print(s);
  assert(s.compare("(0, 3) (1, 2) (2, 1) (3, 5) (4, 8) (7, 7) ")==0);
  assert(t->count()==6);
  assert(t->search(0)==3);
  assert(t->search(1)==2);
  assert(t->search(4)==8);
  assert(t->search(7)==7);
  assert(t->search(2)==1);
  assert(t->search(3)==5);
  assert(t->search(5)==-1);
  t->remove(4);
  s = "";
  t->print(s);
 assert(s.compare("(0, 3) (1, 2) (2, 1) (3, 5) (7, 7) ")==0);
  assert(t->count()==5);
}

int main () {
  GenericSearch<int, int> *t = NULL;

  t = new IndexedKeySearch<int>(10);
  execute(t);  
  delete t;

  t = new SequentialSearch<int, int>(10);
  execute(t);  
  delete t;

  t = new BinarySearch<int, int>(10);
  execute(t);  
  delete t;

  t = new BinarySearchTree<int, int>();
  execute(t);  
  delete t;
  
  return 0;
}
