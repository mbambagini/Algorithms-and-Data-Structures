//this file provides an implementation of the hash table
#include <iostream>
#include <list>
#include <assert.h>
#include <stdlib.h>

using namespace std;

//hash implementation
//the key is assumed integer or string (other types may be supported but an
//implicit cast would be required)
template<class V>
class Hash {
 public:
   //constructor
   //M table size
   //empty value to use when no element is found (instead of using exceptions)
  Hash(int M, V empty) {
    buffer = new list<Node>[M];
	factor = M;
	empty_val = empty;
  }
  ~Hash() {
    if (buffer != NULL)
	  delete[] buffer;
  }

  //insert the pair (key, value);
  void insert(int key, V value);

  void insert(string key, V value) {
    insert(fromStringToInt(key), value);
  }

  //remove the first value with the specified key
  void remove(int key);

  void remove(string key) {
    remove(fromStringToInt(key));
  }

  //search the first element with the specified key
  V search(int key);

  V search(string key) {
    return search(fromStringToInt(key));
  }

  //this function shows the collision (number of keys which share the same
  //hash table cell
  void print();
  
 private:
  class Node {
   public:
    Node (int k, V v): key(k), value(v) {}
    int key;
	V value;
  };

  //hash table size
  int factor;

  //hash table
  list<Node> *buffer;

  //value to return when no element is found
  V empty_val;

  //convert from an integer key in to a hash table index
  int hashFunction (int k) {
    return k % factor;
  }

  //convert a string key in to an integer key (not a hash table index)
  int fromStringToInt (string s);
};

template<class V>
void Hash<V>::print() {
  for (int i = 0; i < factor; i++)
    cout<<i<<":\t "<<buffer[i].size()<<endl;
}

template<class V>
void Hash<V>::remove(int key) {
  int new_key = hashFunction(key);
  for (typename list<Node>::iterator it = buffer[new_key].begin();
       it != buffer[new_key].end(); it++)
    if (it->key == key) {
	  buffer[new_key].erase(it);
	  return;
	}
}

template<class V>
V Hash<V>::search(int key) {
  int new_key = hashFunction(key);
  for (typename list<Node>::iterator it = buffer[new_key].begin();
       it != buffer[new_key].end(); it++)
    if (it->key == key)
	  return it->value;
  return empty_val;
}

template<class V>
void Hash<V>::insert(int key, V value) {
  int new_key = hashFunction(key);
  buffer[new_key].push_front(Node(key, value));
}

template<class V>
int Hash<V>::fromStringToInt (string s) {
  int sum = 0;
  for (int i = 0; i < s.size(); i++)
    sum += s[i];
  return sum;
}

int main() {
  srand(time(0));

  Hash<string> hash(10, "---");

  hash.insert(5, "test1");
  hash.insert(15, "test2");
  hash.insert(7, "test3");
  assert(hash.search(5).compare("test1")==0);
  assert(hash.search(15).compare("test2")==0);
  assert(hash.search(7).compare("test3")==0);
  assert(hash.search(8).compare("---")==0);
  hash.remove(15);
  assert(hash.search(15).compare("---")==0);
  hash.insert("test_key", "test_value");
  assert(hash.search("test_key").compare("test_value")==0);

/*
  Hash<int> hash2(10, -1);
  for (int i = 0; i < 500; i++) {
    int num = rand() & RAND_MAX;
    hash2.insert(num, num+1);
  }
  hash2.print();
*/

  return 0;
}
