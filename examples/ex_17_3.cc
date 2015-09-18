#include <iostream>
#include <assert.h>

using namespace std;

//the main idea is that a trailing 0 is due to the multiplication by 2, so it
//counts the number of times by 2
//note that the multiplication of two odd numbers is always an odd number (no
//trailing 0 introduced)
int countTralingZero (int n) {
  if (n < 2)
    return 0;
  if (n == 2)
    return 1;

  int num_zeros = 1;

  for (int i = 3; i <= n; i++) {
    int tmp = i;
    while ((tmp & 0x01) == 0x00)  {
      num_zeros++;
      tmp = tmp >> 1;
	}
  }

  return num_zeros;
}

int main () {
  assert(countTralingZero(0)==0);
  assert(countTralingZero(1)==0);
  assert(countTralingZero(2)==1);
  assert(countTralingZero(6)==4);
  assert(countTralingZero(10)==8);
  assert(countTralingZero(15)==11);

  return 0;
}
