//this file contains the implementation of a graph which uses adjacency lists
//pros:
//- lower memory than adjacency matrixes with spare graphs (#V+#E)
//- getting the list of adjacent nodes takes O(1)
//cons:
//- implementation and performance of edge/vertex removal/manipolation are slower

#include <iostream>
#include <assert.h>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class Graph {
 public:
  //n is the maximum number of vertexes
  Graph (int n = 10);

  //add a vertex
  bool addNode (const T &a);

  //connect the vertexes a and b with a weighted link
  bool connect (const T &a, const T &b, int cost);

  //Depth-First traversal, starting from a
  void depthFirst (const T &a, string &s);

  //Breadth-First traversal, starting from a
  void breadthFirst(const T &a, string &s);

  virtual ~Graph() {
	delete[] vertexes;
  }

 private:
  //a vertex contains all the links of such a node
  class Vertex {
   public:
	T data;
	list<int> links;
  };

  //vertex array: edge information is contained within them
  Vertex *vertexes;

  //maximum number of nodes
  int num_nodes;

  //actual number of nodes
  int num_actual_nodes;

  //function which is called when a node is visited during a traversal
  void visit(int id, string &s);
};

template<class T>
Graph<T>::Graph(int n): num_nodes(n) {
  num_actual_nodes = 0;
  vertexes = new Vertex[n];
}

template<class T>
bool Graph<T>::addNode (const T &a) {
  if (num_actual_nodes == num_nodes)
	return false;
  vertexes[num_actual_nodes].data = a;
  vertexes[num_actual_nodes].links.clear();
  num_actual_nodes++;
}

template<class T>
bool Graph<T>::connect (const T &a, const T &b, int cost) {
  int id_a = -1, id_b = -1;
  for (int i = 0; i < num_actual_nodes; i++)
    if (vertexes[i].data == a) {
	  id_a = i;
	  break;
	}
  for (int i = 0; i < num_actual_nodes; i++)
	if (vertexes[i].data == b) {
	  id_b = i;
	  break;
	}
  if (id_a == -1 || id_b == -1)
	return false;

  vertexes[id_a].links.push_back(id_b);
  vertexes[id_b].links.push_back(id_a);

  return true;
}

template<class T>
void Graph<T>::breadthFirst(const T &a, string &s) {
  int id = -1;
  for (int i = 0; i < num_actual_nodes; i++)
    if (vertexes[i].data == a) {
	  id = i;
	  break;
	}
  if (id == -1)
    return;

  vector<bool> visited(num_actual_nodes, false);
  queue<int> qu;
  qu.push(id);
  while(!qu.empty()) {
    id = qu.front();
	qu.pop();
	if (visited[id] == true)
	  continue;
    visit(id, s);
	visited[id] = true;
	for (list<int>::iterator it = vertexes[id].links.begin();
	     it != vertexes[id].links.end(); it++)
	  if (!visited[*it])
	    qu.push(*it);
  }
}

template<class T>
void Graph<T>::depthFirst(const T &a, string &s) {
  int id = -1;
  for (int i = 0; i < num_actual_nodes; i++)
    if (vertexes[i].data == a) {
	  id = i;
	  break;
	}
  if (id == -1)
    return;

  vector<bool> visited(num_actual_nodes, false);
  stack<int> st;
  st.push(id);
  while(!st.empty()) {
    id = st.top();
	st.pop();
	if (visited[id] == true)
	  continue;
    visit(id, s);
	visited[id] = true;
	for (list<int>::reverse_iterator it = vertexes[id].links.rbegin();
	     it != vertexes[id].links.rend(); it++)
	  if (!visited[*it])
	    st.push(*it);
  }
}

template<class T>
void Graph<T>::visit(int id, string &s) {
  ostringstream ss;
  ss<<vertexes[id].data<<" ";
  s.append(ss.str());
}

int main () {
  Graph<int> graph;

  graph.addNode(10);
  graph.addNode(7);
  graph.addNode(5);
  graph.addNode(1);
  graph.addNode(2);
  graph.connect(5, 1, 1);
  graph.connect(5, 10, 1);
  graph.connect(10, 7, 1);
  graph.connect(1, 7, 1);
  graph.connect(2, 7, 1);
  graph.connect(2, 5, 1);

  string s("DEPTH-FIRST: ");
  graph.depthFirst(10, s);
  assert(s.compare("DEPTH-FIRST: 10 5 1 7 2 ")==0);

  s = "BREADTH-FIRST: ";
  graph.breadthFirst(10, s);
  assert(s.compare("BREADTH-FIRST: 10 5 7 1 2 ")==0);

  return 0;
}
