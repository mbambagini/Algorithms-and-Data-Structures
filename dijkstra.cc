//this file implements the Dijkstra algorithm for searching the shortest path in
//a graph

#include <iostream>
#include <assert.h>
#include <queue>
#include <set>
#include <stack>
#include <list>
#include <string>
#include <sstream>

using namespace std;

//this class implement a graph using the adjacency list
template<class T>
class Graph {
 public:
  //n is the maximum number of vertexes
  Graph (int n = 10);

  //add a vertex
  bool addNode (const T &a);

  //connect the vertexes a and b with a weighted link
  bool connect (const T &a, const T &b, int cost);

  virtual ~Graph() {
	delete[] vertexes;
  }

  //find the shortest path from start_node to dst_node
  //s contains the path
  int shortestPath(const T& start_node, const T& dst_node, string &s);

 private:

  //an edge contains the destination node and the link cost
  struct Edge {
    int id_node;
	int cost;
	Edge(int n, int c):id_node(n), cost(c) {}
  };

  //a vertex contains all the links of a node
  struct Vertex {
	T data;
	list<Edge> links;
  };

  //convert the value into the node id in vertexes
  int fromValueToId (T v) {
    for (int i = 0; i < num_actual_nodes; i++)
      if (vertexes[i].data == v)
	    return i;
	return -1;
  }
  
  //return the value of the id-th vertex
  T fromIdToValue (int i) {
    if (i < num_actual_nodes)
	  return vertexes[i].data;
	return -1;
  }
  
  //vertex array: edge information is contained within them
  Vertex *vertexes;

  //maximum number of nodes
  int num_nodes;

  //actual number of nodes
  int num_actual_nodes;

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
  int id_a, id_b;

  id_a = fromValueToId(a);
  id_b = fromValueToId(b);

  if (id_a == -1 || id_b == -1)
	return false;

  vertexes[id_a].links.push_back(Edge(id_b, cost));
  vertexes[id_b].links.push_back(Edge(id_a, cost));

  return true;
}

//an infinitive potential is represented as -1
template<class T>
int Graph<T>::shortestPath(const T& start_node, const T& dst_node, string &s) {
  stringstream ss;
  set<int> q;
  vector<int> potential(num_actual_nodes, -1);
  vector<int> predecessor(num_actual_nodes, -1);
  int id_start, id_stop;

  id_start = fromValueToId(start_node);
  id_stop = fromValueToId(dst_node);
  if (id_stop == -1 || id_start == -1)
    return -1;
  if (id_start == id_stop)
    return 0;

  for (int i = 0; i < num_actual_nodes; i++)
    q.insert(i);

  potential[id_start] = 0;

  while(!q.empty()) {
    //find the node with lowest potential and remove it from the queue
    int id = -1;
    for (int i = 0; i < num_actual_nodes; i++)
      if (q.count(i) != 0 && potential[i] != -1 &&
          (id == -1 || potential[id] > potential[i]))
        id = i;

    if (id == -1 || potential[id] == -1)
      return -1;
    q.erase(id);

    //check if its neighbours can be reached through it with a lower cost
    for (typename list<Edge>::iterator it = vertexes[id].links.begin();
         it != vertexes[id].links.end();
         it++) {
      int d = potential[id] + it->cost;
      if (potential[it->id_node] == -1 || potential[it->id_node] > d) {
        potential[it->id_node] = d;
        predecessor[it->id_node] = id;
      }
    }
  }

  //prepare the output string with the path
  int id = id_stop;
  while (id != id_start) {
    ss<<fromIdToValue(id)<<" <- ";
    id = predecessor[id];
  }
  ss<<fromIdToValue(id_start);
  s = ss.str();

  //return the cost
  return potential[id_stop];
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
  graph.connect(10, 7, 2);
  graph.connect(1, 7, 1);
  graph.connect(2, 7, 1);
  graph.connect(2, 5, 4);

  string s;
  assert(graph.shortestPath(5, 5, s) == 0);

  assert(graph.shortestPath(5, 10, s) == 1);
  assert(s.compare("10 <- 5") == 0);

  assert(graph.shortestPath(2, 5, s) == 3);
  assert(s.compare("5 <- 1 <- 7 <- 2") == 0);

  return 0;
}
