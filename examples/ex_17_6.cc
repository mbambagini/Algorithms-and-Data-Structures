#include <iostream>
#include <assert.h>

using namespace std;

struct RangeResult {
  int n;
  int m;
};

//the idea consists of checking is a number is greater than one of next elements
//if so, it finds how many elements it should skips to make the array sorted.
RangeResult computeShortestPart (int ar[], int size) {
  RangeResult res;

  res.n = size;
  res.m = 0;

  bool found = false;

  for (int i = 0; i < (size - 1); i++) {
    int tmp_n = size;
	int tmp_m = 0;
    found = false;
    for (int j = i + 1; j < size; j++) {
	  if (ar[i] > ar[j] && !found) {
        tmp_n = i;
        found = true;
      }
	  if (found && ar[i] < ar[j])
      {
		tmp_m = j - 1;
		found = false;
		break;
      }
	}
	if (tmp_n < res.n)
	  res.n = tmp_n;
	if (tmp_m > res.m)
	  res.m = tmp_m;
  }

  return res;
}

int main () {
  int ar[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 17, 18, 19};
  RangeResult res = computeShortestPart(ar, 13);
  assert(res.n==3 && res.m==9);  

  int ar2[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 18, 17, 19};
  res = computeShortestPart(ar2, 13);
  assert(res.n==3 && res.m==11);

  int ar3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  res = computeShortestPart(ar3, 13);
  assert(res.n==13 && res.m==0);

  return 0;
}
