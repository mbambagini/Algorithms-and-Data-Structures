#include <iostream>
#include <assert.h>

using namespace std;

//the multiplication is exploited as a conditional statement
int findMax (int a, int b) {
  int k = ( (a-b)>>(sizeof(int)*8-1)) & 0x01;
  return a - k * (a-b);
}

int main () {
  assert(findMax (10, 6)==10);
  assert(findMax (6, 10)==10);
  assert(findMax (-2, 6)==6);
  assert(findMax (-2, -6)==-2);
  assert(findMax (2, -6)==2);

  return 0;
}
