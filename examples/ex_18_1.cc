#include <iostream>
#include <assert.h>

using namespace std;

//a and b must be both positive
//the xor operation is the sum of different bits while the and operation (and
//shift)is the sum of two 1s
//the cycle ends when the result of the and operation is 0
int add (int a, int b) {
  int c, d;
  do {
    c = a ^ b;
	d = a & b;
	d = d << 1;
	a = c;
	b = d;
  } while( d != 0);
  return c;
}

int main () {
  assert(add(3, 7) == 10);
  assert(add(7, 3) == 10);
  assert(add(2, 6) == 8);
  assert(add(0, 7) == 7);
  assert(add(7, 0) == 7);
  assert(add(0, 0) == 0);

  return 0;
}
