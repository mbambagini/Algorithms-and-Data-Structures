#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

int computeNum2s (int num) {
  int max_prev_digit = 0;
  int digit_id = 0;
  int count = 0;

  while (num > 0) {
    int digit = num % 10;
	count += digit * max_prev_digit + ( (digit >= 2) ? pow(10, digit_id) : 0);
    max_prev_digit = 10 * max_prev_digit + pow(10, digit_id);
	num /= 10;
    digit_id++;
  }

  return count;
}

int main () {
  assert(computeNum2s(1) == 0);
  assert(computeNum2s(2) == 1);
  assert(computeNum2s(3) == 1);
  assert(computeNum2s(30) == 13);
  assert(computeNum2s(100) == 20);
  assert(computeNum2s(1000) == 300);
  assert(computeNum2s(1351) == 475);
  assert(computeNum2s(1151) == 335);
  return 0;
}
