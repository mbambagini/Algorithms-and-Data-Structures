#include <iostream>
#include <assert.h>
#include <list>

using namespace std;

struct Pair {
  int first;
  int second;
  Pair(int a, int b): first(a), second(b) {}
};

void findPairs (int *values, int n, int sum, list<Pair> &l) {
  for (int i = 0; i < (n - 1); i++) {
    if (values[i] > sum)
      continue;
    for (int j = i + 1; j < n; j++)
      if ((values[i] + values[j]) == sum) {
        l.push_back(Pair(values[i], values[j]));
        l.push_back(Pair(values[j], values[i]));
      }
  }
}

int main () {
  int values[] = {10, 9, 4, 18, -9, 11, 20, 0, 1, 5};

  list<Pair> l;
  findPairs(values, 10, 10, l);

  assert(l.size() == 4); //10+0, 0+10, 9+1, 1+9

  return 0;
}

