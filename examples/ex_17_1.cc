#include <iostream>
#include <assert.h>

using namespace std;

void swap (int &a, int &b) {
  b = a + b;
  a = b - a;
  b = b - a;  
}

int main () {
  int a = 10;
  int b = 6;

  swap(a, b);
  assert(b == 10 && a == 6);
  
  return 0;
}
