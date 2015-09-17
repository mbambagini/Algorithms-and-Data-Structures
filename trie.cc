//tries (shortcut of trTRIEval) are a kind of tree extremely useful to implement
//dictionaries.
//Unlike the BSTs whose nodes contain the keys, each level of a trie (or more
//generally Digit Search Trees - DST) contains a part of the key.
//Compared to set<key>, tries are a bit faster (O(L) where L is the length of
//the key, instead of O(N) where N is the number of stored elements) and it is
//extremely easy to look up similar words (useful for auto complete features)
//
//Tries are characterized from the following features:
//- the root is empty ("")
//- if v is father of w, then the v's key is a prefix of w's (each node is a
//  prefix of its sub-trees
//Unlike BSTs, the insertion order does not affect the tree structure

#include <iostream>
#include <list>
#include <queue>
#include <assert.h>

using namespace std;

class Trie {
 public:
  Trie(): num_words(0), root(new Node('\0')) {}
  
  //insert a word
  void insert (string word) {
    insert(word, root, 0);
  }

  //return if a word exists
  bool search (string word) {
    Node* ptr = search(word, root, 0);
    return (ptr != NULL && ptr->word());
  }

  void print() {
    string s;
    print (root, s);
  }

  //return the words with the given prefix
  void autoComplete(string prefix, list<string>& l) {
    Node *n = search(prefix, root, 0);
    if (n == NULL)
      return;
    autoComplete(prefix, l, n);
  }

  //return the total number of stored words
  int count () {
    return num_words;
  }

 private:
  class Node {
   public:
    Node(char key, bool word = false) : key_part(key), is_a_word(word) { }
	void set_key (char key) { key_part = key; }
	char key () { return key_part; }
	void set_word (bool w) { is_a_word = w; }
	bool word () { return is_a_word; }
	list<Node*> l;
   private:
    //key
    char key_part;
	//return if the node is a word or an intermediate node
    bool is_a_word;
  };

  void insert(string word, Node* h, int letter);
  Node* search(string word, Node* h, int letter);
  void print (Node* ptr, string s = "");
  void autoComplete(string prefix, list<string>& l, Node* ptr);
  
  int num_words;

  Node *root;
};

void Trie::print (Node* ptr, string s) {
  if (ptr == NULL)
    return;

  if (ptr->key() != '\0')
    s += ptr->key();
  if (ptr->word())
    cout<<"STRING: "<<s<<endl;

  for (list<Node*>::iterator it = ptr->l.begin(); it != ptr->l.end(); it++)
    print(*it, s);
}

void Trie::insert (string word, Node* h, int letter) {
  if (h == NULL)
    return;

  for (list<Node*>::iterator it = h->l.begin(); it != h->l.end(); it++)
    if ((*it)->key() == word[letter])
	  return insert(word, *it, letter+1);
  Node* ptr = new Node(word[letter]);
  h->l.push_back(ptr);
  if (letter == word.size()) {
    num_words = h->word() ? num_words : num_words+1;
	h->set_word(true);
	return;
  }
  return insert(word, ptr, letter+1);
}

Trie::Node* Trie::search (string word, Node* h, int letter) {
  if (h == NULL)
    return NULL;

  if (letter == word.size() && h->key() == '\0' && h->l.size() == 0)
    return h;

  for (list<Node*>::iterator it = h->l.begin(); it != h->l.end(); it++)
    if ((*it)->key() == word[letter]) {
	  if (letter < (word.size()-1))
	    return search(word, *it, letter+1);
	  if (letter == (word.size()-1))
	     return *it;
	}
  return NULL;
}

void Trie::autoComplete(string prefix, list<string>& l, Node* ptr) {
  if (ptr->word())
    l.push_back(prefix);
  for (list<Node*>::iterator it = ptr->l.begin(); it != ptr->l.end(); it++)
    autoComplete(prefix+(*it)->key(), l, *it);
}

int main () {
  Trie trie;

  trie.insert("t");
  trie.insert("test");
  trie.insert("text");
  trie.insert("textual");
  trie.insert("temporary");
  trie.insert("alpha");
  trie.insert("al");
  assert(trie.count()==7);
  //trie.print();
  assert(trie.search("te")==0);
  assert(trie.search("text")==1);
  list<string> l;
  trie.autoComplete("tex", l);
  assert(l.size()==2);
  assert(l.front().compare("text") == 0);
  assert(l.back().compare("textual") == 0);
  return 0;
}
