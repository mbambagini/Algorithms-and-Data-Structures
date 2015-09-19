#include <iostream>
#include <sstream>
#include <assert.h>

using namespace std;

class BinarySearchTree {
 public:
  BinarySearchTree () {
    num_actual_elements = 0;
    head = NULL;
  }

  ~BinarySearchTree () {
    //todo
  }

  void convert () {
    BSTNode *a, *b;
    list_head = NULL;
    convert(head, NULL, a, b);
  }

  int count () {
    return num_actual_elements;
  }

  void insert (int value) {
    if (head == NULL) {
      head = new BSTNode(value);
      num_actual_elements = 1;
      return;
    }
    insert(value, head);
  }

  void print(string &s) {
    print(s, head);
  }

  void printList(string &s);

 private:

  class BSTNode {
   public:
    int item;
    BSTNode *left;
    BSTNode *right;
    BSTNode (int value) {
      item = value;
      right = left = NULL;
    }
  };

  void print (string &s, BSTNode* ptr);
  
  void insert (int value, BSTNode *ptr);  

  //BST root
  BSTNode *head;
  BSTNode *list_head;

  //it states the actual number of nodes in the BST
  int num_actual_elements;

  void convert (BSTNode* ptr, BSTNode* prev, BSTNode* &min_node,
                BSTNode* &max_node);

};

//the main idea consists of:
//- assigning to the left pointer the highest value of the left sub-tree
//- assigning to the right pointer the lowest value of the right sub-tree
void BinarySearchTree::convert (BSTNode* ptr, BSTNode* prev,
                                BSTNode* &min_node,
                                BSTNode* &max_node) { //max 
  if (ptr == NULL) {
    max_node = min_node = NULL;
    return;
  }

  BSTNode *a , *b, *c, *d;

  //recursion
  convert(ptr->left, ptr, a, b);
  convert(ptr->right, ptr, c, d);

  //handle first node - list head
  if (a == NULL && b == NULL && list_head == NULL)
    list_head = ptr;

  //modify pointers
  ptr->left = (b == NULL) ? ((list_head == ptr) ? NULL : prev) : b;
  ptr->right = (c == NULL) ? prev : c;

  //special case: modifiy the pointer of another node
  if (b != NULL && b->item < ptr->item)
    b->right = ptr;
  //special case: highest node
  if (prev == NULL && d != NULL)
    d->right = NULL;

  //return values
  min_node = (a == NULL) ? ptr : a;
  max_node = (d == NULL) ? ptr : d;
}

void BinarySearchTree::printList (string &s) {
  stringstream ss;
  BSTNode* ptr = list_head;
  while (ptr != NULL) {
    ss<<ptr->item<<" ";
    ptr = ptr->right;
  }
  s = ss.str();
}

void BinarySearchTree::insert (int value, BSTNode *ptr) {
  if (value == ptr->item)
    return;
  if (value > ptr->item) {
    //right sub-tree
    if (ptr->right == NULL) {
      ptr->right = new BSTNode(value);
      num_actual_elements++;
      return;
    } else
      insert(value, ptr->right);
  } else {
    //left sub-tree
    if (ptr->left == NULL) {
      ptr->left = new BSTNode(value);
      num_actual_elements++;
      return;
    } else
      insert(value, ptr->left);
  }
}

int main () {
  BinarySearchTree bst;
  bst.insert(4);
  bst.insert(2);
  bst.insert(3);
  bst.insert(1);
  bst.insert(0);
  bst.insert(5);
  bst.insert(6);

  bst.convert();
  string s;
  bst.printList(s);
  assert(s.compare("0 1 2 3 4 5 6 ")==0);

  return 0;
}

