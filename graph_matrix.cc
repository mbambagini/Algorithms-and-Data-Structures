//this file provides an implementation of a graph based on adjacency matrixs

#include <iostream>
#include <assert.h>
#include <queue>
#include <stack>
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
    for (int i = 0; i < num_nodes; i++)
	  delete[] edges[i];
	delete[] edges;
	delete[] vertexes;
  }

 private:
  //links between nodes/vertexes
  int **edges;

  //array with the conversion from T to the internal id
  T *vertexes;

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
  vertexes = new T[n];
  edges = new int*[n];
  for (int i = 0; i < n; i++)
	edges[i] = new int[n];
  for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	  edges[i][j] = 0;
}

template<class T>
bool Graph<T>::addNode (const T &a) {
  if (num_actual_nodes == num_nodes)
	return false;
  vertexes[num_actual_nodes++] = a;
}

template<class T>
bool Graph<T>::connect (const T &a, const T &b, int cost) {
  int id_a = -1, id_b = -1;
  for (int i = 0; i < num_actual_nodes; i++)
    if (vertexes[i] == a) {
	  id_a = i;
	  break;
	}
  for (int i = 0; i < num_actual_nodes; i++)
	if (vertexes[i] == b) {
	  id_b = i;
	  break;
	}
  if (id_a == -1 || id_b == -1)
	return false;

  edges[id_a][id_b] = edges[id_b][id_a] = cost;

  return true;
}

template<class T>
void Graph<T>::breadthFirst(const T &a, string &s) {
  int id = -1;
  for (int i = 0; i < num_actual_nodes; i++)
    if (vertexes[i] == a) {
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
    for (int i = 0; i < num_actual_nodes; i++)
	  if (edges[id][i] != 0 && !visited[i])
	    qu.push(i);
  }
}

template<class T>
void Graph<T>::depthFirst(const T &a, string &s) {
  int id = -1;
  for (int i = 0; i < num_actual_nodes; i++)
    if (vertexes[i] == a) {
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
    for (int i = num_actual_nodes - 1; i >= 0; i--)
	  if (edges[id][i] != 0 && !visited[i])
	    st.push(i);
  }
}

template<class T>
void Graph<T>::visit(int id, string &s) {
  ostringstream ss;
  ss<<vertexes[id]<<" ";
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
  assert(s.compare("DEPTH-FIRST: 10 7 1 5 2 ")==0);

  s = "BREADTH-FIRST: ";
  graph.breadthFirst(10, s);
  assert(s.compare("BREADTH-FIRST: 10 7 5 1 2 ")==0);

  return 0;
}
