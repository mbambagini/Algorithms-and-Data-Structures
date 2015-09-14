#include <iostream>
#include <assert.h>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class Tree {
 public:
  Tree(): root(NULL) {}

  //insert a node with value==son and with the specified father
  //return false if the father does not exists, true otherwise
  //if the tree is empty, the node is always inserted
  bool insert(T father, T son);

  //Depth-First Pre-Order traversal
  void depthFirstPreOrder(string &s) {
    depthFirstPreOrder(s, root);
  }
  
  //Depth-First In-Order traversal
  void depthFirstInOrder(string &s) {
    depthFirstInOrder(s, root);
  }
  
  //Depth-First Post-Order traversal
  void depthFirstPostOrder(string &s) {
    depthFirstPostOrder(s, root);
  }

  //Breadth-First traversal
  void breadthFirst(string &s);

  //return the number of nodes
  int countNodes ();

 private:
  //internal representation of a node
  class TreeNode {
   public:
    T value;
	TreeNode* left;
	TreeNode* right;
  };

  bool insert(T father, T son, TreeNode *n);
  void depthFirstPreOrder(string &s, TreeNode *n);
  void depthFirstInOrder(string &s, TreeNode *n);
  void depthFirstPostOrder(string &s, TreeNode *n);

  int countNodes (TreeNode* n);

  //function which is called when a node is visited during a traversal
  void visit(string &s, TreeNode *n);

  //tree root
  TreeNode* root;

};

template<class T>
int Tree<T>::countNodes () {
  return countNodes(root);
}

template<class T>
int Tree<T>::countNodes (TreeNode* n) {
  //inefficient implementation: a variable is better
  if (n == NULL)
    return 0;
  return 1+countNodes(n->left)+countNodes(n->right);
}

template<class T>
void Tree<T>::breadthFirst(string &s) {
  if (root == NULL)
    return;
  queue<TreeNode*> arr;
  arr.push(root);

  while(!arr.empty()) {
    TreeNode* n = arr.front();
	arr.pop();
	visit(s, n);
	if (n->left != NULL)
	  arr.push(n->left);
	if (n->right != NULL)
	  arr.push(n->right);
  }
}
  
template<class T>
void Tree<T>::depthFirstPreOrder(string &s, TreeNode *n) {
  if (n == NULL)
    return;
  visit(s, n);
  depthFirstPreOrder(s, n->left);
  depthFirstPreOrder(s, n->right);
}

template<class T>
void Tree<T>::depthFirstInOrder(string &s, TreeNode *n) {
  if (n == NULL)
    return;
  depthFirstInOrder(s, n->left);
  visit(s, n);
  depthFirstInOrder(s, n->right);
}

template<class T>
void Tree<T>::depthFirstPostOrder(string &s, TreeNode *n) {
  if (n == NULL)
    return;
  depthFirstPostOrder(s, n->left);
  depthFirstPostOrder(s, n->right);
  visit(s, n);
}

template<class T>
void Tree<T>::visit(string &s, TreeNode *n) {
  ostringstream ss;
  ss<<n->value<<" ";
  s.append(ss.str());
}

template<class T>
bool Tree<T>::insert(T father, T son) {
  if (root == NULL) {
    root = new TreeNode;
	root->value = son;
	root->left = NULL;
	root->right = NULL;
	return true;
  }

  return insert(father, son, root);
}

template<class T>
bool Tree<T>::insert(T father, T son, TreeNode* node) {
  if (node == NULL)
    return false;

  if (node->value == father) {
    TreeNode* n = new TreeNode;
	n->value = son;
	n->left = NULL;
	n->right = NULL;
	if (node->left == NULL) {
	  node->left = n;
	  return true;
	}
	if (node->right == NULL) {
	  node->right = n;
	  return true;
	}
    return false;
  }

  return insert(father, son, node->left) || insert(father, son, node->right);
}

int main () {
  Tree<int> tree;

  //build the following tree:
  //     1        root
  //  2     3     first level
  // 4 7   5 6    second level - leaves
  assert(tree.countNodes()==0);
  assert(tree.insert(1, 1)==true);
  assert(tree.countNodes()==1);
  assert(tree.insert(1, 2)==true);
  assert(tree.countNodes()==2);
  assert(tree.insert(1, 3)==true);
  assert(tree.countNodes()==3);
  assert(tree.insert(2, 4)==true);
  assert(tree.countNodes()==4);
  assert(tree.insert(3, 5)==true);
  assert(tree.countNodes()==5);
  assert(tree.insert(3, 6)==true);
  assert(tree.countNodes()==6);
  assert(tree.insert(2, 7)==true);
  assert(tree.countNodes()==7);
  assert(tree.insert(10, 11)==false);
  assert(tree.countNodes()==7);

  string s("PRE-ORDER: ");
  tree.depthFirstPreOrder(s);
  assert(s.compare("PRE-ORDER: 1 2 4 7 3 5 6 ")==0);

  s = "IN-ORDER: ";
  tree.depthFirstInOrder(s);
  assert(s.compare("IN-ORDER: 4 2 7 1 5 3 6 ")==0);

  s = "POST-ORDER: ";
  tree.depthFirstPostOrder(s);
  assert(s.compare("POST-ORDER: 4 7 2 5 6 3 1 ")==0);

  s = "BREADTH-FIRST: ";
  tree.breadthFirst(s);
  assert(s.compare("BREADTH-FIRST: 1 2 3 4 7 5 6 ")==0);

  return 0;
}
