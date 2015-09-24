//This is a classical problem in which:
//- you have an initial amount of resources F
//- visiting the node i costs cost[i] and provides gain[i] (gain[i] < cost[i])
//- each node can be visited only once
//- a node can be visited if and only if the initial amount of resources is
//  higher than or equal to its cost
//- the objective consists of returning the maximum number of nodes you can
//  visit given an initial amount of resources
//
//The algorithm is NP and it has to consider all possible paths which are N!
//The problem is equivalent to pick a destination node and running the same 
//algorithm on a problem domain with N-1 possible nodes

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

//class which implements the algorithm in question
class NodeVisitor {
 public: 
  //return the maximum number of hopes
  //R: initial number of resources
  //cost: vector of costs (cost.size() == gain.size())
  //gain: vector of rewarding
  int MaximumSteps(int R, vector <int> cost, vector <int> gain);
 private:
  //recursive function
  //number: # of actual hopes
  //r: list of remaining nodes to consider (false: already chosen,
  //   true: still available)
  //id: id of the chosen node to be considered
  int MaximumStepsRec (int R, vector<bool> r, int number = 0, int id = -1);
  //input cost vector
  vector<int> cost_;
  //input reward vector
  vector<int> gain_;
};

int NodeVisitor::MaximumSteps (int R, vector <int> cost, vector <int> gain) {
  assert(cost.size() == gain.size());
  cost_ = cost;
  gain_ = gain;
  vector<bool> r(cost.size(), true);
  return MaximumStepsRec(R, r);
}

int NodeVisitor::MaximumStepsRec (int R, vector<bool> r, int number, int id) {
  if (id != -1) {
    r[id] = false;
    R = R - cost_[id] + gain_[id];
  }
  if (R < 0)
    return number - 1;

  int max = number;
  for (int i = 0; i < r.size(); i++)
    if (R >= cost_[i] && r[i]) {
      int num = MaximumStepsRec(R, r, number+1, i);
      if (num > max) max = num;
    }
  return max;
}

int main () {

  NodeVisitor x;

  vector<int> gain1(1, 0);
  vector<int> cost1(1, 0);
  assert(x.MaximumSteps(10, cost1, gain1) == 1);

  vector<int> gain2(2, 0); gain2[1] = 1;
  vector<int> cost2(2, 4); cost2[1] = 6;
  assert(x.MaximumSteps(9, cost2, gain2) == 2);

  return 0;
}
