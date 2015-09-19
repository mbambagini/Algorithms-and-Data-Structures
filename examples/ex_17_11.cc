#include <iostream>
#include <assert.h>
#include <stdlib.h>

using namespace std;

int rand5 () {
  return rand() % 5;
}

int rand7 () {
  return ((rand5() + rand5() + rand5() + rand5() + rand5() + rand5() +
           rand5()) % 7);
}

#define SAMPLES		10000

int main () {
  srand(time(0));
  int arr[7] = {0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < SAMPLES; i++)
    arr[rand7()]++;
  for (int i = 0; i < 7; i++)
    assert(arr[i] >= (SAMPLES/7)*0.7 && arr[i] <= (SAMPLES/7)*1.3);

  return 0;
}

